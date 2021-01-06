# Thumbnail Auto Crop

The IMDB ([OMDB](https://www.omdbapi.com/)) API provides a thumbnail image when querying
something like a TV show episode. Most times the image is not in a 16:9 aspect ratio
though, and manually cropping thumbnails for several seasons of a TV show is tedious.
This program automates the cropping of the thumbnails by detecting faces in the images
and cropping them in frame.
