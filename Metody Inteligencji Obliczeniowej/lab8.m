data = csvread('lab8_data.csv');

cv = cvpartition(size(data, 1), 'HoldOut', 0.2);
idx = cv.test;

trainData = data(~idx, :);
testData = data(idx, :);

x_train = trainData(:, 1:3);
y_train = trainData(:, 4);

% opt1 = genfisOptions('SubtractiveClustering');
% opt1.SquashFactor = 1.1;
% opt1.AcceptRatio = 0.14;
% opt1.RejectRatio = 0.05;
% fis1 = genfis(x_train, y_train, opt1);


% [x,mf] = plotmf(fis1,'input',1);
% subplot(3,2,1)
% plot(x,mf)
% xlabel('input 1')
% [x,mf] = plotmf(fis1,'input',2);
% subplot(3,2,2)
% plot(x,mf)
% xlabel('input 2')
% [x,mf] = plotmf(fis1,'input',3);
% subplot(3,2,3)
% plot(x,mf)
% xlabel('input 3')

% opt2 = genfisOptions('FCMClustering', 'FISType', 'mamdani');
% opt2.NumClusters = size(fis1.Rules, 2);
% 
% fis2 = genfis(x_train, y_train, opt2);

% [x,mf] = plotmf(fis2,'input',1);
% subplot(3,2,4)
% plot(x,mf)
% xlabel('input 1')
% [x,mf] = plotmf(fis2,'input',2);
% subplot(3,2,5)
% plot(x,mf)
% xlabel('input 2')
% [x,mf] = plotmf(fis2,'input',3);
% subplot(3,2,6)
% plot(x,mf)
% xlabel('input 3')

% opt3 = anfisOptions();
% opt3.InitialFIS = 2;
% 
% fis3 = anfis(trainData, opt3);

x_test = testData(:, 1:3);
y_test = testData(:, 4);

y1_train = evalfis(fis1, x_train);
y1_test = evalfis(fis1, x_test);

y2_train = evalfis(fis3, x_train);
y2_test = evalfis(fis3, x_test);

y3_train = evalfis(fis3, x_train);
y3_test = evalfis(fis3, x_test);

train_error_1 = immse(y1_train, y_train)
test_error_1 = immse(y1_test, y_test)

train_error_2 = immse(y2_train, y_train)
test_error_2 = immse(y2_test, y_test)

train_error_3 = immse(y3_train, y_train)
test_error_3 = immse(y3_test, y_test)




