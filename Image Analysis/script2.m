im = double(imread('zubr.jpg'))/255;
im = 1 - rgb2gray(im);

% subplot(2, 2, 1);
% imshow(im);
% 
% s = 13;
% f = ones(s) / s^2; %(filtr rozmywajacy/dolnoprzepustowy)
% im = imfilter(im, f);
% 
% subplot(1, 2, 2);
% imshow(im);

% subplot(1, 2, 1);
% imshow(im);
% 
% s = 3;
% f = -ones(s); % (filtr wyostrzajacy/gornoprzepustowy)
% f((s+1)/2, (s+1)/2) = s^2;
% im = imfilter(im, f);
% 
% subplot(1, 2, 2);
% imshow(im);

% subplot(1, 2, 1);
% imshow(im);
% 
% s = 3;
% f = -ones(s);
% f((s+1)/2, (s+1)/2) = s^2 - 1; % suma wag = 0 (wykrywanie krawedzi)
% im = imfilter(im, f);
% 
% subplot(1, 2, 2);
% imshow(im);

% subplot(1, 2, 1);
% imshow(im);
% 
% im = medfilt2(im, [13, 13]); %filtr mediany macierz 3x3
% 
% subplot(1, 2, 2);
% imshow(im);

% subplot(1, 3, 1);
% imshow(im);
% 
% subplot(1, 3, 2);
% imhist(im);
% 
% t = graythresh(im);
% imb = im;
% % imb(imb < t) = 0; %binaryzacja obrazu
% % imb(imb >= t) = 1;
% imb = imbinarize(im, t); % /imbinarize(im, 'adaptive') - np. do tekstu
% 
% subplot(1, 3, 3);
% imshow(imb);


imb = imbinarize(im, t);
subplot(1, 3, 1);
imshow(imb);
% imb = imerode(imb, ones(3)); %erozja
% imb = imdilate(imb, ones(3)); %dylatacja

% erozja -> dylatacja (morfologiczne otwarcie - funkcja imopen)
% dylatacja -> erozja (imclose)

imb2 = imb;
imb = imopen(imb, ones(3));
subplot(1, 3, 2);
imshow(imb);

imb2 = imclose(imb2, ones(3));
subplot(1, 3, 3);
imshow(imb2);

% funkcja fspecial - tworzy filtry








