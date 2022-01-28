import os
from PIL import Image

file_num = 0
folder_name = input('Enter the name of folder, where all images are located (default is "images"): ')
check = True
for root, dirs, files in os.walk(folder_name):
    for file in files:
        check = False
        image = Image.open(folder_name + '/' + file)
        file_num += 1
        print()
        print('File from folder "' + folder_name + '" number', file_num)
        print('Name of the file:', image.filename)
        print('Size of the file:', image.size)
        print("File's DPI:", image.info.get('dpi'))
        print('Depth of color:', image.mode)
        print('Compression:', image.info.get('compression'))
if check:
    print('\nThere are no any files in the folder "' + folder_name + '", try other folder...')
input('\nProgram finished the work. Press any key for exit...')
