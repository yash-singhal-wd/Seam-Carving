<!-- Date -->
# Image_Resizer

# **Seam Carving Content Aware Image Resizing**

An implementation of the seam-carving algorithm for content-aware image resizing. Users can resize an image by defining its desired height and width in pixels.

## **Table of Contents**
<!-- add table of contents having link -->

## **About**

### **What is Seam Carving?**

- Seam-carving is a content-aware image resizing method where the image size is reduced pixel by pixel, either in height or width.
- Vertical seams connect pixels from the top to the bottom with one pixel in each row, and horizontal seams connect pixels from left to right with one pixel in each column.
- **Steps**:
    - **Energy Calculation**: Every pixel has RGB values. Calculate energy for each pixel using, for example, the dual-gradient energy function. (However, other energy functions can be chosen.
    - **Seam Identification**: Identify the lowest energy seam.
    - **Seam Removal**: Eliminate the identified seam.

## **Program Flow**

1. Extract RGB values for each pixel from **`./data/input/sample.jpeg`** and save them into **`./data/input/rgb_in.txt`**.
2. Load RGB values from **`./data/input/rgb_in.txt`** into a 3D matrix.
3. Execute the seam carving algorithm.
4. Store RGB values of the resized image into **`./data/output/rgb_out.txt`**.
5. Create **`./data/output/sample_out.jpeg`** from **`./data/output/rgb_out.txt`**.

 The Python script **`./src/driver.py`** does the 1st and 5th steps. The corresponding **`./src/main.cpp`** file, triggered by the Python script, handles the 2nd and 4th steps.

## **Getting Started**
    

### **Dependencies**

- **Pillow (Python Imaging Library)**: Utilized for extracting RGB pixel values and regenerating images from these values.
    
    ```bash
    pip install Pillow
    ```
    
    > Note: This Python script is compatible with Linux/Mac OS only. Windows users may request the input text file (rgb_in.txt) to begin working on the problem.
    > 

### **How to Run**

1. Navigate to the `**Image_Resizer**` directory in the terminal.
2. Run the **`driver.py`** Python script located in **`/src`**. Pass the input image filename (must reside in **`/data/input`**) as a command line argument.
    
    ```bash
    python ./src/driver.py sample1.jpeg
    
    ```