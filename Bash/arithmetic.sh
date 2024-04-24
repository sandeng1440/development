
#!/usr/bin/env bash
set -euo pipefail

a=10
b=20

val=$(($a + $b))
echo "$val"

arr=()
read -p "Enter the values you want to add. (Space separated): " numbers
arr+=($numbers)

total=0
for k in "${arr[@]}"; do
  total=$(($total + k)) 
done
echo "The total is $total"

