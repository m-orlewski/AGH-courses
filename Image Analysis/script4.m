clear; clc;

im = double(imread('kaczki.jpg'))/255;

im = 1 - rgb2gray(im);

im = imbinarize(im);
im = imclose(im, ones(11));

% morfologia - cechy ksztaltu
% topologia, liczba eulera ksztaltu

% im = bwmorph(im, 'remove'); % im - imerode
% imshow(im);

% im = bwmorph(im, 'skel', 5);
% im = bwmorph(im, 'skel', 10);
% im = bwmorph(im, 'skel', 15);
% im = bwmorph(im, 'skel', 20);
% imshow(im);
% im = bwmorph(im, 'skel', 30);
% im = bwmorph(im, 'skel', Inf);
% sk = bwmorph(im, 'skel', 50); % im - imerode
% imshow(sk); % szkielet - zbior punktow rownoodlegle od 2 roznych krawedzi obrazu

% endp = bwmorph(sk, 'endpoints');
% imshow(endp);

% brp = bwmorph(sk, 'branchpoints');
% imshow(brp);

% shr = bwmorph(im, 'shrink', 10);
% shr = bwmorph(im, 'shrink', 20);
% shr = bwmorph(im, 'shrink', 30);
% shr = bwmorph(im, 'shrink', 40);
% shr = bwmorph(im, 'shrink', Inf);
% 
% imshow(shr); % redukuje do jednego punktu

% th = bwmorph(im, 'thin', 10);
% th = bwmorph(im, 'thin', 20);
% th = bwmorph(im, 'thin', 30);
% th = bwmorph(im, 'thin', 40);
% th = bwmorph(im, 'thin', Inf);
% imshow(th); % erozja ktora nie usunie linii

% th = bwmorph(im, 'thicken', 10);
% th = bwmorph(im, 'thicken', 20);
% th = bwmorph(im, 'thicken', 50);
% th = bwmorph(im, 'thicken', 100);
% th = bwmorph(im, 'thicken', Inf);
% imshow(th); % dylatacja zachowujaca krawedzie (segmentacja przez pogrubianie - obraz podzielony na segmenty z obiektami)

% l = bwlabel(im);
% imshow(label2rgb(l));
% imshow(l == 3);s

% th = bwmorph(im, 'thicken', Inf);
% l =  bwlabel(th);
% % imshow(l == 2);
% imc = double(imread('kaczki.jpg'))/255;
% imshow((l == 2) .* imc .* im); %maskowanie

% im(:, [1, end]) = 1;
% im([1, end], :) = 1; % dodajemy ramke
% d = bwdist(im); %odl piksela od najblizszego bialego piksela
% imshow(d, [0, max(d, [], 'all')]);

% l = watershed(d);
% imshow(label2rgb(l));

%normy L1, L2, .. Linf/Lmax - argument do bwdist

im(:, [1, end]) = 1;
im([1, end], :) = 1; % dodajemy ramke
d = bwdist(im, 'chessboard'); %odl piksela od najblizszego bialego piksela
imshow(d, [0, max(d, [], 'all')]);

