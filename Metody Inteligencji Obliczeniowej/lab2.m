% red = randn(2, 50);
% blue = randn(2, 50);
% green = randn(2, 50);
% yellow = randn(2, 50);
% 
% red = [red(1,:)+2; red(2,:)];
% blue = [blue(1,:)-2; blue(2,:)];
% green = [green(1,:); green(2,:)+2];
% yellow = [yellow(1,:)+2; yellow(2,:)-2];
% 
% x_train = [red, blue, green, yellow];
% y_train = [zeros(1, 100), ones(1, 100); zeros(1, 50), ones(1, 50), zeros(1, 50), ones(1, 50)];
% 
% 
% net = perceptron;
% net = configure(net, x_train, y_train);
% net = train(net, x_train, y_train);
% view(net);

red2 = randn(2, 1000);
blue2 = randn(2, 1000);
green2 = randn(2, 1000);
yellow2 = randn(2, 1000);

red2 = [red2(1,:)+2; red2(2,:)];
blue2 = [blue2(1,:)-2; blue2(2,:)];
green2 = [green2(1,:); green2(2,:)+2];
yellow2 = [yellow2(1,:)+2; yellow2(2,:)-2];

x_test = [red2, blue2, green2, yellow2];
y_expected = [zeros(1, 2000), ones(1, 2000); zeros(1, 1000), ones(1, 1000), zeros(1, 1000), ones(1, 1000)];
y_test = net(x_test);

%plotconfusion(y_expected, y_test);

y_test2 = zeros(1, 4000);
for i = 1:4000
    if y_test(1, i) == 0 && y_test(2, i) == 0
        y_test2(i) = 1;
    elseif y_test(1, i) == 0 && y_test(2, i) == 1
        y_test2(i) = 2;
    elseif y_test(1, i) == 1 && y_test(2, i) == 0
        y_test2(i) = 3;
    else
        y_test2(i) = 4;
    end
end

y_expected2 = [ones(1, 1000), ones(1, 1000)+1, ones(1, 1000)+2, ones(1, 1000)+3];
plotconfusion(y_expected2, y_test2);




