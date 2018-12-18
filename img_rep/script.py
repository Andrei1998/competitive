import glob
import os
import sys

from math import exp
from random import shuffle
from PIL import Image
import numpy as np

# Read image from disk to NumPy array
def read_img_to_array(name):
    img = Image.open(name)
    return np.array(img)

# Remove (turn into black) percent% pixels of an image
def damage_image(img, percent):    
    n, m, c = img.shape
    all = [(a, b) for a in range(n) for b in range(m)]
    shuffle(all)
    cnt = len(all)
    all = all[0 : (percent * cnt // 100)]
    for p in all:
        for c in range(3):
            a, b = p
            img[a][b][c] = 0
    return img

# Write NumPy-represented 3D RGB array as BMP file
def write_array_to_disk(name, img, show = False):
    img = Image.fromarray(img, 'RGB')
    if show:
        img.show()
    img.save(name, "BMP")  

# Iterate all files matching "img/*.*", remove percent%
# of their pixels and save the results as "damaged_img/*.bmp"
def damage_all(percent):
   directory = "damaged_img_" + str(percent)
   if not os.path.exists(directory):
       print("Creating directory " + directory + " ...")
       os.makedirs(directory)
       print("Successful!!!\n")
   for file in glob.glob("img/*.*"):
        print("Damaging " + file + " ...")
        output_file = directory + file[3:-4] + ".bmp"
        if os.path.exists(output_file):
            print("File " + output_file + " already exists!!!\n")
        else:        
            img = read_img_to_array(file)
            img = damage_image(img, percent)
            write_array_to_disk(output_file, img) # bug: if extension is not 3 chars long
            print("Successful!!!\n")
       
# Get a 2 * lspan + 1 by 2 * cspan + 1 pixel tableau centered at (row, col)
# Out of bounds pixels become (0, 0, 0)
def assemble_tableau(img, row, col, lspan, cspan):
    n, m, c = img.shape
    mat = np.zeros((2 * lspan + 1, 2 * cspan + 1, 3))
    for i in range(-lspan, lspan + 1):
        for j in range(-cspan, cspan + 1):
            l, c = row + i, col + j
            if l >= 0 and l < n and c >= 0 and c < m:
                mat[i + lspan][j + cspan] = img[l][c]
    return mat
    
# Average of non-black pixels in tableau
def predict_sum(t):
    n, m, c = t.shape
    sum, cnt = np.zeros(3), 0
    for i in range(n):
        for j in range(m):
            if t[i][j][0] > 0 or t[i][j][1] > 0 or t[i][j][2] > 0:
                sum += t[i][j]
                cnt += 1    
    if cnt == 0:
        return np.zeros(3)
    else:
        return sum / cnt
        
# Gaussian average of non-black pixels in tableau
def predict_gauss(t):
    n, m, c = t.shape
    mid_i, mid_j = (n - 1) // 2, (m - 1) // 2
    sum, cnt = 0.0, 0.0
    for i in range(n):
        for j in range(m):
            if t[i][j][0] > 0 or t[i][j][1] > 0 or t[i][j][2] > 0:
                dist_sq = (i - mid_i) * (i - mid_i) + (j - mid_j) * (j - mid_j)
                w = exp(-dist_sq / 2)
                sum += w * t[i][j]
                cnt += w
    if cnt < 1E-20:
        return sum
    else:
        return sum / cnt
    
# Restore damaged image, returning image as new NumPy array
def restore_img(img, predict): 
    n, m, c = img.shape
    restored_img = np.array(img)
    last = -1
    for i in range(n):
        for j in range(m):
            current = ((i * m + j + 1) * 100) // (n * m)
            if current > last:
                last = current
                sys.stdout.write(str(current) + "% ")
                sys.stdout.flush()
            if img[i][j][0] == 0 and img[i][j][1] == 0 and img[i][j][2] == 0:
                t = assemble_tableau(img, i, j, 6, 6)
                restored_img[i][j] = predict(t)
    sys.stdout.write("\n");
    sys.stdout.flush()
    return restored_img

# Iterate all files matching "damaged_img$percent/*.bmp", restore
# colors of black pixels and save the results as "restored_img$percent/*.bmp"
def restore_all(predict, percent, show = False):
    directory = "restored_img_" + str(predict.__name__) + "_" + str(percent)
    if not os.path.exists(directory):
       print("Creating directory " + directory + " ...")
       os.makedirs(directory)
       print("Successful!!!\n")
    for file in glob.glob("damaged_img_" + str(percent) + "/*.bmp"):
        print("Restoring " + file + " ...")
        output_file = "restored_img_" + str(predict.__name__) + file[11:]
        if os.path.exists(output_file):
            print("File " + output_file + " already exists!!!\n")
        else:        
            img = read_img_to_array(file)
            print("Restoring with " + str(predict.__name__) + " ...")
            restored_img = restore_img(img, predict)
            if show:
                Image.fromarray(restored_img).show()
            write_array_to_disk(output_file, restored_img)    
            print("Successful!!!\n")

damage_percent = 95
damage_all(damage_percent)
restore_all(predict_gauss, damage_percent)
