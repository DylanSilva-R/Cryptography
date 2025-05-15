def file_to_binary(input_path, output_path):
    """
    Converts a file to binary representation and saves it to another file
    Each character is converted to its 8-bit binary representation
    """

    try:
        # Open the input file in binary mode to properly handle all characters
        with open(input_path, 'rb') as input_file:
            data = input_file.read()
        
        binary_values = []
        # Process each byte
        for byte in data:
            # Convert to 8-bit binary representation
            binary = format(byte, '08b')
            binary_values.append(binary)
        
        # Join with spaces for readability
        binary_string = ' '.join(binary_values)
        
        # Write to output file
        with open(output_path, 'w') as output_file:
            output_file.write(binary_string)
        
        print(f"Conversion complete! Binary data saved to '{output_path}'")
        return True
        
    except Exception as e:
        print(f"Error converting file to binary: {e}")
        return False

def main():
    import sys
    if len(sys.argv) != 3:
        print("Usage: python convert_to_binary.py <input_file> <output_file>")
        return
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    file_to_binary(input_file, output_file)

if __name__ == "__main__":
    main()