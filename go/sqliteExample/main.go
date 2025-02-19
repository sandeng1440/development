package main

import (
	"database/sql"
	"log"
	"os"

	_ "github.com/mattn/go-sqlite3" // Import go-sqlite3 library
)

// const (
// 	DBNAME = "sqliteExampleDB.db"
// )

func main() {
	os.Remove("sqlite-database.db") // I delete the file to avoid duplicated records.
	// SQLite is a file based database.

	log.Println("Creating sqlite-database.db...")
	file, err := os.Create("sqlite-database.db") // Create SQLite file
	if err != nil {
		log.Fatal(err.Error())
	}
	file.Close()
	log.Println("sqlite-database.db created")

	sqliteDatabase, _ := sql.Open("sqlite3", "sqlite-database.db") // Open the created SQLite File
	defer sqliteDatabase.Close()                                   // Defer Closing the database
	createTable(sqliteDatabase)                                    // Create Database Tables

	// INSERT RECORDS
	insertStudent(sqliteDatabase, "0001", "Liana Kim", "Bachelor", 2.2)
	insertStudent(sqliteDatabase, "0002", "Glen Rangel", "Bachelor", 2.2)
	insertStudent(sqliteDatabase, "0003", "Martin Martins", "Master", 24.0)
	insertStudent(sqliteDatabase, "0004", "Alayna Armitage", "PHD", 4)
	insertStudent(sqliteDatabase, "0005", "Marni Benson", "Bachelor", 9)
	insertStudent(sqliteDatabase, "0006", "Derrick Griffiths", "Master", 10)
	insertStudent(sqliteDatabase, "0007", "Leigh Daly", "Bachelor", 11.1)
	insertStudent(sqliteDatabase, "0008", "Marni Benson", "PHD", 22)
	insertStudent(sqliteDatabase, "0009", "Klay Correa", "Bachelor", 0.1)

	// DISPLAY INSERTED RECORDS
	displayStudents(sqliteDatabase)
}

func createTable(db *sql.DB) {
	createStudentTableSQL := `CREATE TABLE student (
		"idStudent" integer NOT NULL PRIMARY KEY AUTOINCREMENT,		
		"code" TEXT,
		"name" TEXT,
		"program" TEXT,
		"amount" float
	  );` // SQL Statement for Create Table

	log.Println("Create student table...")
	statement, err := db.Prepare(createStudentTableSQL) // Prepare SQL Statement
	if err != nil {
		log.Fatal(err.Error())
	}
	statement.Exec() // Execute SQL Statements
	log.Println("student table created")
}

// We are passing db reference connection from main to our method with other parameters
func insertStudent(db *sql.DB, code string, name string, program string, amount float64) {
	log.Println("Inserting student record ...")
	insertStudentSQL := `INSERT INTO student(code, name, program, amount) VALUES (?, ?, ?, ?)`
	statement, err := db.Prepare(insertStudentSQL) // Prepare statement.
	// This is good to avoid SQL injections
	if err != nil {
		log.Fatalln(err.Error())
	}
	_, err = statement.Exec(code, name, program, amount)
	if err != nil {
		log.Fatalln(err.Error())
	}
}

func displayStudents(db *sql.DB) {
	rows, err := db.Query("SELECT * FROM student ORDER BY name")
	if err != nil {
		log.Fatal(err)
	}
	defer rows.Close()
	for rows.Next() { // Iterate and fetch the records from result cursor
		var id int
		var code string
		var name string
		var program string
		var amount float64
		rows.Scan(&id, &code, &name, &program, &amount)
		log.Println("Student: ", code, " ", name, " ", program, " ", amount)
	}
}
