# Ray Tracer

Simple ray tracer following the Ray Tracing in One Weekend book.

## Example Render

A world has been created along with a couple of different materials for us. Feel free to make your own scene in the main.cpp file.

Clone the repository

```sh
git clone https://github.com/luisacosta971/ray-tracer.git
```
Change into the directory
```sh
cd ray-tracer
```
Run the Makefile which will compile, link, and execute the program. It may take a while to fully render based on a few parameters such as hittables and samples per pixel.
```sh
make all
```
This will create a PPM file. You might need to download a third-party image viewer. Check which ones are available based on your operating system.

Below is an example world. Note that the sample_per_pixel was set to 10 to save time on rendering. Increasing this improvse the quality but will also take longer to render.

![image](https://github.com/luisacosta971/ray-tracer/assets/71291014/477b5010-b2e1-404a-b70d-bcd8423cbee1)
