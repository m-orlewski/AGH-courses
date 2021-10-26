clear; clc;


im = imread('zubr.jpg');
im = double(im) / 255;

% h = 3;
% w = 2;
% i = 1;
% 
% for j = 1:3
%     subplot(h, w, i); i=i+1;
%     imshow(im(:, :, j));
%     subplot(h, 2, i); i=i+1;
%     imhist(im(:, :, j));
% end

% szarosc

im = mean(im, 3); % usrednianie w 3 wymiarze
im = max(im, [], 3);
im = min(im, [], 3);
YUV = [.299, .587, .114];
YUV = permute(YUV, [1, 3, 2]); % wektor wag
im = im .* YUV; % funkcja rgb2grey
im = sum(im, 3);
% subplot(1, 2, 1);
% imshow(im);
% subplot(1, 2, 2);
% imhist(im);

% jasnosc

% b = .2;
% imb = im + b;
% imb(imb > 1) = 1;
% imb(imb < 0) = 0;
% 
% x = 0 : 1/255 : 1;
% y = x + b;
% y(y > 1)=1;
% y(y < 0)=0;
% 
% subplot(3, 2, 1);
% imshow(im);
% subplot(3, 2, 2);
% imshow(imb);
% subplot(3, 2, 3);
% imhist(im)
% subplot(3, 2, 4);
% imhist(imb);
% subplot(3, 2, 5);
% plot(x, y); % wykres przeksztalcenia
% ylim([0, 1]);

%  kontrast
% 
% c = .5;
% imc = im  * c;
% imc = (im - .5) * c + .5; % kontrast wzgledem .5
% imc(imc > 1) = 1;
% 
% x = 0 : 1/255 : 1;
% y = x * c;
% y(y > 1)=1;
% y(y < 0)=0;
% 
% subplot(3, 2, 1);
% imshow(im);
% subplot(3, 2, 2);
% imshow(imc);
% subplot(3, 2, 3);
% imhist(im)
% subplot(3, 2, 4);
% imhist(imc);
% subplot(3, 2, 5);
% plot(x, y); % wykres przeksztalcenia
% ylim([0, 1]);

% gamma
% g = .5;
% img = im .^ g;
% 
% x = 0 : 1/255 : 1;
% y = x .^ g;
% 
% subplot(3, 2, 1);
% imshow(im);
% subplot(3, 2, 2);
% imshow(img);
% subplot(3, 2, 3);
% imhist(im)
% subplot(3, 2, 4);
% imhist(img);
% subplot(3, 2, 5);
% plot(x, y); % wykres przeksztalcenia
% ylim([0, 1]);

% wyrownanie histogramu
imh = histeq(im);
subplot(1, 2, 1);
imshow(imh);
subplot(1, 2, 2);
imhist(imh);



















