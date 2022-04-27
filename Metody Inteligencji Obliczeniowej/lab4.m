% x_train = transpose(Lab5training(:, 1:4));
% y_train = transpose(Lab5training(:, 5:7));

% net = feedforwardnet(100);
% net.divideFcn = 'dividetrain';
% net.layers{1}.transferFcn = 'logsig';
% net.trainParam.epochs = 100;
% 
% net = configure(net, x_train, y_train);
% net = train(net, x_train, y_train);
% view(net);

% x_test = transpose(Lab5training(:, 1:4));
% y_expected = transpose(Lab5training(:, 5:7));
% 
% y_test = net(x_test);
% 
% plotconfusion(y_expected, y_test);


training_img = training.images;
training_labels = training.labels;
x_train = zeros(60000, 784);
y_train = full(ind2vec(training_labels' + 1));

for i = 1:60000
    t = training_img(:,:,i);
    x_train(i, :) = t(:);
end

testing_img = test.images;
testing_labels = test.labels;
x_test = zeros(10000, 784);

for i = 1:10000
    t = testing_img(:,:,i);
    x_test(i, :) = t(:);
end

y_expected = full(ind2vec(testing_labels' + 1));


net = feedforwardnet(10);
net.divideFcn = 'dividetrain';
net.layers{1}.transferFcn = 'logsig';
net.trainParam.epochs = 5;

x_train = x_train';
train_ind = randsample(60000, 1000);

net = configure(net, x_train(:,train_ind), y_train(:,train_ind));
net = train(net, x_train(:,train_ind), y_train(:,train_ind));
view(net);

x_test = x_test';
y_test = net(x_test);
plotconfusion(y_expected, y_test);



