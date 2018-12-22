# Image RePaint

Python script for image [inpainting](https://en.wikipedia.org/wiki/Inpainting) of dead pixels.
Supports multiple block based recovery modes:

* Arithmetic average of non-dead pixels 
* [Gaussian](https://en.wikipedia.org/wiki/Gaussian_blur#Mathematics) average of non-dead pixels
* WIP: [Orthogonal Matching Pursuit](https://en.wikipedia.org/wiki/Matching_pursuit)

### Prerequisites

NumPy and PIL (i.e. Pillow) need to be installed in order for the script to work properly. Install them by running this command from the project directory:

```
pip install -r requirements.txt
```

### Example

Consider the non-damaged image data/img/dog1.jpg:

<img src="data/img/dog1.jpg" width="400" height="266" alt="image could not load">

By blackening 70 percent of its pixels ("damaging" it) we get data/damaged_img_70/dog1.bmp:

<img src="data/damaged_img_70/dog1.bmp" width="400" height="266" alt="image could not load">

Attempting to restore the initial image using the Gaussian Averaging Algorithm we get data/restored_img_predict_gauss_70/dog1.bmp:

<img src="data/restored_img_predict_gauss_70/dog1.bmp" width="400" height="266" alt="image could not load">

## Built With

* [Pillow](https://python-pillow.org/) - Python Imaging Library (PIL fork)
* [NumPy](http://www.numpy.org/) - Python Linear Algebra Library

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [README template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
