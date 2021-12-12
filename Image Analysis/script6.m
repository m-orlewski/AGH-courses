clear; clc;

% im = double(imread('ptaki.jpg'))/255;
im2 = double(imread('ptaki2.jpg'))/255;

% h = 3;
% w = 2;
% i = 1;
% 
% for j = 1:3
%      subplot(h, w, i); i=i+1;
%      imshow(im(:, :, j));
%     subplot(h, 2, i); i=i+1;
%     imhist(im(:, :, j));
% end


% im = 1 - rgb2gray(im);
% t = 0.72;
% im = imbinarize(im, t);
% im = imclose(im, ones(25));

% r - jasne, g - gradient, b - ciemne 
% pozbywamy sie g i binaryzujemy tylko 1 i b
% b = imbinarize(im(:,:,3));
% r = imbinarize(im(:,:,1));
% im = ~b|r;
% im = imopen(im, ones(5));
% im = 1 - rgb2gray(im);
im2 = 1 - im2;
im2 = imbinarize(im2(:,:,3));
im2 = imclose(im2, ones(3));
% imshow(im2);

l2 = bwlabel(im2);
n2 = max(l2, [], 'all'); % ilosc obiektow


prop2 = regionprops(l2==4, 'all');
% struktura zawierajaca properties obiektu o label==4
%centroid - srednia w kilku wymiarach, srodek masy
%boudingbox - prostokat w ktorym sie miesci obiekt


% Lf - obwod figury, Sf - pole figury
% kolo takie ze: Lf = Lk(obwod kola) => R = L/2pi
% Sf=Sk(pole kola) => R = sqrt(S/pi)
% stosunek C = Rs/Rl (0, 1] - wspolczynnik ksztaltu
% 1/C - 1 [0, inf) - wspolczynnik Malinowskiej - podobienstwo obiektu do
% kola
% wsp. BloirBliss - srednia odleglosc srodka masy od punktu (dla kola male)
% wsp. Daniellsona - srednia odleglosc punktu od krawedzi (dla kola duze)
% wsp. Haralick - laczy poprzednie wspolczynniki
% wsp. Ferreta - stosunek osi (dla kola = 1)

fun2 = {@AO5RCircularityL, @AO5RCircularityS, @AO5RShape, @AO5RMalinowska, @AO5RBlairBliss, @AO5RDanielsson, @AO5RFeret, @AO5RHaralick};
   

wsp2 = zeros(n2, length(fun2));
   
for i = 1:n2
   for j = 1: length(fun2)
        wsp2(i, j) = fun2{j}(l2==i);
   end
end


for i = 1:size(wsp2, 1)
    area2(i) = sum(l2==i, 'all');
end

script5;

out = area2 < 900;
wsp3 = wsp2(out, :);
wsp2(out, :) = [];

n = size(wsp, 1);
n2 = size(wsp2, 1);
n3 = size(wsp3, 1);

in = [wsp', wsp2', wsp3'];
out = [repmat([1;0;0], [1, n]), repmat([0;1;0], [1, n2]), repmat([0;0;1], [1, n3])];

nn = feedforwardnet;
nm = train(nn, in, out);

nm(in(:, 1));
nm(in)










