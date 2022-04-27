% red = randn(2, 50);
% blue = randn(2, 50);
% 
% both = [blue(1, :) + 2; blue(2, :)];
% x_train = [red, both];
% y_train = [zeros(1, 50), ones(1, 50)];
% 
% net = perceptron;
% net = train(net, x_train, y_train);
% view(net);

red2 = randn(2, 500);
blue2 = randn(2, 500);

both2 = [blue2(1, :)+2; blue2(2, :)];
x_test = [red2, both2];
y_expected = [zeros(1, 500), ones(1, 500)];

y_test = net(x_test);
plotconfusion(y_test, y_expected);






