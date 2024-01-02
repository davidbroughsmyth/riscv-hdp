import sys, getopt

def main(argv):
   inputfile = ''
   outputfile = ''
   count = False
   
   try:
      opts, args = getopt.getopt(argv,"hci:o:",["ifile=","ofile="])

   except:
      print("Unhandled option")
      sys.exit()

   for opt, arg in opts:
      if opt == '-h':
         print(f'{sys.argv[0]} -i <inputfile> -o <outputfile>' + "\n" + "flags: -ci or -c -i to count instructions, -h this help")
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg
      elif opt in ("-o", "--ofile"):
         outputfile = arg
      elif opt in ("-c"):
         count = True

   with open(inputfile, 'r') as file:
        assembly_code = file.read()
   lines = assembly_code.split('\n')
   unique_instructions = set()
   for line in lines[5:]:
       line = line.strip()
       if line and not line.startswith('#'):
          parts = line.split()
          if len(parts) >= 3:
             instruction = parts[2]
             unique_instructions.add(instruction)

   if outputfile != "":
      with open(outputfile, 'w') as file:
           if count == True:
               file.write(f"Number of different instructions: {len(unique_instructions)}" + "\n")
           for instruction in unique_instructions:
               file.write(instruction + "\n")
   else:
     if count == True:
	     print(f"Number of different instructions: {len(unique_instructions)}")
	     print("List of unique instructions:")
     for instruction in unique_instructions:
         print(instruction)

if __name__ == "__main__":
   main(sys.argv[1:])
