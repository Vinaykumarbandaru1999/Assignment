#!/bin/bash

# Check for the correct number of command line arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <filepath> <manufacturer>"
    exit 1
fi

# Assign command line arguments to variables
filepath="$1"
manufacturer="$2"

# Check if the file exists and is readable
if [ ! -f "$filepath" ] || [ ! -r "$filepath" ]; then
    echo "Error: File not found or not readable."
    exit 1
fi

# Create a temporary file to store the modified content
tmpfile=$(mktemp)

# Initialize variables to store the original and previous manufacturer values
original_manufacturer=""
previous_manufacturer=""

# Loop through the file line by line
while IFS= read -r line; do
    # Check if the line contains the VEHICLE_MANUFACTURER variable
    if [[ "$line" == "VEHICLE_MANUFACTURER="* ]]; then
        # Extract the current manufacturer value
        original_manufacturer="${line#*=}"

        # Replace the current manufacturer value with the new manufacturer
        line="VEHICLE_MANUFACTURER=$manufacturer"
    fi

    # Append the line to the temporary file
    echo "$line" >> "$tmpfile"
done < "$filepath"

# If the original manufacturer value is not empty, add the previous manufacturer variable
if [ -n "$original_manufacturer" ]; then
    echo "PREVIOUS_VEHICLE_MANUFACTURER=$original_manufacturer" >> "$tmpfile"
fi

# Replace the original file with the temporary file
mv "$tmpfile" "$filepath"

# Optionally, you can log the script operations
log_file="script.log"
echo "$(date): Script executed on $filepath with manufacturer '$manufacturer'" >> "$log_file"

echo "Script completed successfully."
