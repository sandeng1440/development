package main

import (
	"database/sql"
	"encoding/csv"
	"fmt"
	"io"
	"log"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

func main() {
	csvFilePath := "inflation-rates.csv" // Replace with your CSV file path
	dbFilePath := "inflation-rates.db"   // Replace with your desired DB file path

	err := csvToSQLite(csvFilePath, dbFilePath)
	if err != nil {
		log.Fatalf("Error converting CSV to SQLite: %v", err)
	}

	fmt.Println("CSV data imported to SQLite successfully!")
}

func csvToSQLite(csvFilePath, dbFilePath string) error {
	// 1. Read CSV file
	file, err := os.Open(csvFilePath)
	if err != nil {
		return fmt.Errorf("failed to open CSV file: %w", err)
	}
	defer file.Close()

	reader := csv.NewReader(file)

	// 2. Determine table name (from filename)
	tableName := strings.TrimSuffix(filepath.Base(csvFilePath), filepath.Ext(csvFilePath))

	// 3. Read header row (column names)
	header, err := reader.Read()
	if err != nil {
		return fmt.Errorf("failed to read CSV header: %w", err)
	}

	// 4. Open/Create SQLite database
	db, err := sql.Open("sqlite3", dbFilePath)
	if err != nil {
		return fmt.Errorf("failed to open SQLite database: %w", err)
	}
	defer db.Close()

	// 5. Create table
	err = createTable(db, tableName, header)
	if err != nil {
		return fmt.Errorf("failed to create table: %w", err)
	}

	// 6. Insert data
	err = insertData(db, tableName, header, reader)
	if err != nil {
		return fmt.Errorf("failed to insert data: %w", err)
	}

	return nil
}

// func createTable(db *sql.DB, tableName string, header []string) error {
// 	// Basic type inference (all TEXT for simplicity)
// 	var columns []string
// 	for _, col := range header {
// 		columns = append(columns, fmt.Sprintf("%s TEXT", col))
// 	}
// 	createQuery := fmt.Sprintf("CREATE TABLE IF NOT EXISTS %s (%s)", tableName, strings.Join(columns, ", "))
//
// 	_, err := db.Exec(createQuery)
// 	if err != nil {
// 		return fmt.Errorf("failed to execute CREATE TABLE statement: %w", err)
// 	}
//
// 	return nil
// }

func inferType(value string) string {
	if _, err := strconv.Atoi(value); err == nil {
		return "INTEGER"
	}
	if _, err := strconv.ParseFloat(value, 64); err == nil {
		return "REAL"
	}
	return "TEXT"
}

func createTable(db *sql.DB, tableName string, header []string, reader *csv.Reader) error {
	// Read a few rows to infer types
	numRows := 3 // Number of rows to inspect
	var sampleData [][]string
	for i := 0; i < numRows; i++ {
		row, err := reader.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			return fmt.Errorf("failed to read sample CSV row: %w", err)
		}
		sampleData = append(sampleData, row)
	}

	// Reset the reader to the beginning of the data (after the header)
	_, err := reader.file.Seek(0, io.SeekStart)
	if err != nil {
		return fmt.Errorf("failed to seek to beginning of file: %w", err)
	}
	_, err = reader.Read() // Skip the header again

	var columns []string
	for i, col := range header {
		dataType := "TEXT" // Default
		// Infer type based on sample data
		for _, row := range sampleData {
			if i < len(row) {
				inferredType := inferType(row[i])
				if inferredType != "TEXT" {
					dataType = inferredType // Use the first non-TEXT type found
					break
				}
			}
		}
		columns = append(columns, fmt.Sprintf("%s %s", col, dataType))
	}

	createQuery := fmt.Sprintf("CREATE TABLE IF NOT EXISTS %s (%s)", tableName, strings.Join(columns, ", "))

	_, err = db.Exec(createQuery)
	if err != nil {
		return fmt.Errorf("failed to execute CREATE TABLE statement: %w", err)
	}

	return nil
}

func insertData(db *sql.DB, tableName string, header []string, reader *csv.Reader) error {
	// Prepare the INSERT statement
	placeholders := strings.Repeat("?,", len(header))
	placeholders = placeholders[:len(placeholders)-1] // Remove trailing comma
	insertQuery := fmt.Sprintf("INSERT INTO %s VALUES (%s)", tableName, placeholders)

	stmt, err := db.Prepare(insertQuery)
	if err != nil {
		return fmt.Errorf("failed to prepare INSERT statement: %w", err)
	}
	defer stmt.Close()

	// Read and insert data rows
	for {
		row, err := reader.Read()
		if err == io.EOF {
			break // End of file
		}
		if err != nil {
			return fmt.Errorf("failed to read CSV row: %w", err)
		}

		// Convert row data to interface{} slice for Exec
		var args []interface{}
		for _, val := range row {
			args = append(args, val)
		}

		_, err = stmt.Exec(args...)
		if err != nil {
			return fmt.Errorf("failed to execute INSERT statement: %w", err)
		}
	}

	return nil
}
