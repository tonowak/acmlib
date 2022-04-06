import os, sys

if len(sys.argv) == 1:
    testing_dir = 'code'
else:
    testing_dir = sys.argv[1]

root_dir = os.getcwd()
todolist = []
for root, subdirs, files in os.walk(root_dir + '/' + testing_dir):
    if 'main.cpp' in files:
        code_name = root.split('/')[-2:]
        code_name = '/'.join(code_name)
        if 'headers' in root.split('/'):
            continue

        # changing folder because of includes' while compiling
        os.chdir(root)

        if 'test.cpp' in files:
            # compiling and running the test.cpp file
            print("Compiling", code_name)
            if os.system('g++ -std=c++17 -O3 -Wall -Wextra -Wshadow test.cpp') != 0:
                print('Failed testing :(')
                sys.exit(1)
            print('Testing', code_name)
            if os.system('./a.out 1') != 0:
                os.remove('a.out')
                sys.exit(1)

            # remove created files
            os.remove('a.out')
            tested = True
        else:
            # merging file with headers and checking if it compiles
            print("Compiling", code_name)
            os.system('cp ' + root_dir + '/code/utils/headers/main.cpp a.cpp')
            os.system('cat main.cpp >> a.cpp')
            os.system('sed -i "s/#pragma once//" a.cpp')
            os.system('echo "int main(){}" >> a.cpp')
            if os.system('g++ -std=c++17 -Wall -Wextra -Wshadow a.cpp') != 0:
                print('Failed compile :(')
                os.remove('a.cpp')
                sys.exit(1)

            # checking what kind of testing was done
            if 'submit.txt' in files:
                print('Has submission')
                tested = True
            elif '.notesting' in files:
                print('Skipping testing')
                tested = True
            else:
                print('Not tested at all :(')
                tested = False

            # remove created files
            os.remove('a.cpp')
            os.remove('a.out')

        todolist.append((tested, code_name))

print("Updating readme")
os.chdir(root_dir)
with open('README.md', 'r') as readme_f:
    # getting the old todolist
    readme_old_content = readme_f.read()
    readme_split = readme_old_content.split('\n##')
    i_testing = [readme_split.index(l) for l in readme_split if l.startswith(' Testing status')]
    assert len(i_testing) == 1
    i_testing = i_testing[0]
    status_strings = readme_split[i_testing].split('\n')[1:]
    while len(status_strings) and status_strings[-1] == '':
        status_strings = status_strings[:-1]
    path_to_status = dict([(s[6:], s[3] == 'x') for s in status_strings])

    # updating with new info
    for status, name in todolist:
        path_to_status[name] = status

    # converting back to text
    status_strings = ['- [' + ('x' if path_to_status[name] else ' ') + '] ' + name for name in path_to_status]
    readme_split[i_testing] = ' Testing status\n' + '\n'.join(status_strings)
    readme_new_content = '\n##'.join(readme_split)
with open('README.md', 'w') as readme_f:
    readme_f.write(readme_new_content)

