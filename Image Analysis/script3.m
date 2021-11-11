im = double(imread('opera.jpg')) / 255.;
im = rgb2gray(im);

fim = fft2(im);
A = abs(fim);
phi = angle(fim);

maxA = max(A, [], 'all');

%imshow(log(A), [0, log(maxA)]);

%imshow(fftshift(log(A)), [0, log(maxA)]);
%imshow(phi, [-pi, pi]);

%A(5,10) = 10^5;
%phi(1,1) = phi(1,1) + pi;
Z = A .* exp(1i * phi);
im2 = ifft2(Z);
im2 = abs(im2);imshow(im);

%imshow(im2);

[h, w] = size(im);
f = fspecial('average', [9,9]);
ff = fft2(f, h, w);
fA = abs(ff);

maxF = max(fA, [], 'all');
minF = min(fA, [], 'all');

%imshow(log(fA), log([minF, maxF]));
A = A .* fA;
imshow(fftshift(log(A)), [0, log(maxA)]);

im3 = ifft2(A .* exp(1i * phi));
