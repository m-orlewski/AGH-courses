f = @(x) 2 * sin(4.3*x - 2) + 7 * cos(-x + 3.5);

a = 10;

x_train = rand(1, 50) * a;
y_train = f(x_train);

net = feedforwardnet(20);
net = configure(net, x_train, y_train);
net = train(net, x_train, y_train);
% net.layers{1}.transferFcn = 'purelin';
view(net);

x_test = rand(1, 200) * a;
y_test = net(x_test);
y_expected = f(x_test);

MSE = perform(net, y_expected, y_test);

[x_test, sortIndex] = sort(x_test);
y_test = y_test(sortIndex);
y_expected = y_expected(sortIndex);

plot(x_test, y_test, x_test, y_expected);

