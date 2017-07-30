import os


def files_in_dir(absolute_dir):
    files = []
    dirs = []

    os.chdir(absolute_dir)
    files_or_dirs = os.listdir()
    for f in files_or_dirs:
        f = os.path.join(absolute_dir, f)
        if(os.path.isfile(f)):
            files.append(f)
        elif(os.path.isdir(f)):
            dirs.append(f)
        else:
            print("Seems not so right:{}".format(f))

    return files, dirs

def remove_but_file(absolute_file):
    import shutil
    file_dir = os.path.dirname(absolute_file)
    file_name = os.path.basename(absolute_file)
    for f in os.listdir(file_dir):
        if f == file_name:
            continue

        try:
            f = os.path.join(file_dir, f)
            print("Going to remove:{}\n".format(f))
            #wait = input("PRESS ENTER TO CONTINUE.")

            if(os.path.isfile(f)):
                os.remove(f)
            elif(os.path.isdir(f)):
                # os.removedirs(f)
                shutil.rmtree(f)
        except:
            print('error occurs while removing file/dir {}'.format(f))
            wait = input("PRESS ENTER TO CONTINUE.")

if __name__ == '__main__':

    # dir_name = 'H:/projects/hardware_tweaking/cmake_projects/test'
    dir_name = 'C:/Users/miao/Documents/Arduino/libraries/AccelStepperDecorate/examples'

    alldir = set()
    allfiles = set()
    alldir.add(dir_name)


    while len(alldir) > 0:
        newdirs = []
        newfiles = []
        for dir in alldir:
            #print("HERE\n")
            print(dir)
            # alldir.remove(dir)
            files, dirs = files_in_dir(dir)
            newfiles.extend(files)
            newdirs.extend(dirs)

        print("New files len:", len(newfiles))
        #alldir = alldir.union(newdirs)
        alldir = set(newdirs)
        allfiles = allfiles.union(newfiles)

    
    for file in allfiles:
        print(file)
        if file.endswith('.ino'):
            remove_but_file(file)


    # remove_but_file("C:/Users/miao/Documents/Arduino/libraries/AccelStepperDecorate/examples/AccleStepperDecorateExamples/DistanceOrAngleTranslation/DistanceOrAngleTranslation.ino")