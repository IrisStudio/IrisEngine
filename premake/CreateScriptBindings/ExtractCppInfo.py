import CppHeaderParser
from os import walk

def main():
    directory = "."
    for root, dirs, files in walk(directory):
        print root
        for file in files:
            if file.endswith(".h"):
                cppHeader = CppHeaderParser.CppHeader(file)
                tabs = "\t"
                print tabs + file
                if "IS_BINDEABLE" in cppHeader.defines:
                    for class_name, class_info in cppHeader.classes.iteritems():
                        tabs = "\t\t"
                        print tabs + class_name + " inherits: " + str([d['class'] for d in class_info['inherits']])
                        tabs = "\t\t\t"
                        for method in class_info['methods']['public']:
                            line = str(method['returns']) + " " + str(method['name']) + "("
                            for param in method['parameters']:
                                line = line + param['type'] + ", "
                            if len(method['parameters']) == 0:
                                line = line + ")"
                            else:
                                line = line[:-2] + ")"
                            if method['constructor']:
                                line = "constructor: " + line
                            if method['destructor']:
                                line = "destructor: " + line
                            line = tabs + line
                            print line
    
if __name__ == "__main__":
    main();