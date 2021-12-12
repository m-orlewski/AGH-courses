%clear; clc;

im = double(imread('ptaki.jpg'))/255;
% imshow(im);
% 
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
b = imbinarize(im(:,:,3));
r = imbinarize(im(:,:,1));
im = ~b|r;
im = imopen(im, ones(5));

l = bwlabel(im);
n = max(l, [], 'all'); % ilosc obiektow


prop = regionprops(l==4, 'all');
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

fun = {@AO5RCircularityL, @AO5RCircularityS, @AO5RShape, @AO5RMalinowska, @AO5RBlairBliss, @AO5RDanielsson, @AO5RFeret, @AO5RHaralick};
%    
% 
wsp = zeros(n, length(fun));
   
for i = 1:n
   for j = 1: length(fun)
        wsp(i, j) = fun{j}(l==i);
   end
end



m = mean(wsp);
s = std(wsp);
out = abs(wsp-m)./s;

out = out > 1.8;
out = max(out, [], 2)

wsp(out, :) = []; %usuwamy obiekty ktore odstaja wspolczynnikami od reszty

wsp








