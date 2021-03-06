import CppHeaderParser
import json
from os import walk, path, makedirs

def main():
    info = {}
    directory = "../../Engine/"
    for root, dirs, files in walk(directory):
        if "Bindings" not in root:
            info[root] = {}
            for file in files:
                bind_code = ""
                if file.endswith(".h"):
                    try:
                        info[root][file] = {}
                        cppHeader = CppHeaderParser.CppHeader(path.join(root, file))
                        if "IS_BINDEABLE" in cppHeader.defines:
                            #bind_code = bind_code + '#include "ScriptManager.h"\n\n'
                            bind_code = bind_code + '#include "' + path.join(root, file) + '"\n\n'
                            bind_code = bind_code + "namespace binding\n{\n"
                            for class_name, class_info in cppHeader.classes.iteritems():
                                bind_code = bind_code + "\t" + class_name + "()\n\t{\n"
                                info[root][file][class_name] = {}
                                info[root][file][class_name]['inherits'] = [d['class'] for d in class_info['inherits']]
                                info[root][file][class_name]['constructors'] = []
                                info[root][file][class_name]['destructor'] = []
                                info[root][file][class_name]['methods'] = []
                                for method in class_info['methods']['public']:
                                    params = [p['type'] for p in method['parameters']]
                                    key = 'methods'
                                    if method['constructor']:
                                        key = 'constructors'
                                        bind_code = bind_code + '\t\tchai.add(chaiscript::constructor<' + class_name + '('
                                        for p in params:
                                            bind_code = bind_code + p + ", "
                                        if len(params) > 0:
                                            bind_code = bind_code[:-2]
                                        bind_code = bind_code + ')>(), "' + class_name + '");\n'
                                    elif method['destructor']:
                                        key = 'destructor'
                                    else:
                                        bind_code = bind_code + '\t\tchai.add(chaiscript::fun(&' + class_name + '::' + method['name'] + '), "' + method['name'] + '");\n'                            
                                    info[root][file][class_name][key].append({'name': method['name'], 'returns': method['returns'], 'parameters': []})
                                    for param in method['parameters']:
                                        info[root][file][class_name][key][-1]['parameters'].append(param['type'])
                            bind_code = bind_code + "\t}\n}\n"
                            #print(json.dumps(info, indent=4))
                            path_to_save = "Bindings" + root.replace('../../Engine', '')
                            file_to_save = path_to_save + "/" + class_name + "Binding.cpp"
                            if not path.exists(path.dirname(file_to_save)):
                                try:
                                    makedirs(path.dirname(file_to_save))
                                except OSError as exc: # Guard against race condition
                                    if exc.errno != errno.EEXIST:
                                        raise
                            with open(file_to_save, 'w') as f:
                                f.write(bind_code)                            
                            print bind_code
                    except:
                        pass
    
if __name__ == "__main__":
    main();