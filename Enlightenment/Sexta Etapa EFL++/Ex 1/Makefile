all:
	g++ -o evas_image evas_image.cc -DEFL_BETA_API_SUPPORT=1 -DEFL_EO_API_SUPPORT=1 `pkg-config --libs --cflags eo ecore-evas evas ecore eo-cxx eina-cxx evas-cxx ecore-cxx` -std=c++11
