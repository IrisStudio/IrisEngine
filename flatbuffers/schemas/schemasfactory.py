from subprocess import check_output
from os import walk, path, getcwd

def main():
    fb_exe = '"../flatc.exe"'
    fb_args = "--cpp --no-includes"
    
    root_dir = getcwd()
    target_dir = "..\\..\\Engine"
    
    for subdir, dirs, files in walk(root_dir):
        for file in files:
            filename, file_extension = path.splitext(file)
            if file_extension == ".fbs":
                fb_out = path.join(subdir.replace(root_dir,target_dir), file).replace(file,"io\\"+file_extension.replace(".",""))
                #print " ".join([fb_exe,fb_args,"-o",fb_out,subdir+file])
                check_output(" ".join([fb_exe,fb_args,"-o",fb_out,path.join(subdir, file)]), shell=True)
    
if __name__ == "__main__":
    main()