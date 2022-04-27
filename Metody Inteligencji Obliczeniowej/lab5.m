% emb = fastTextWordEmbedding;
% 
% data = readLexicon;

idx = data.Label == "Positive";
head(data(idx,:))

idx = data.Label == "Negative";
head(data(idx,:))

idx = ~isVocabularyWord(emb,data.Word);
data(idx,:) = [];

numWords = size(data,1);
cvp = cvpartition(numWords,'HoldOut',0.2);
dataTrain = data(training(cvp),:);
dataTest = data(test(cvp),:);

wordsTrain = dataTrain.Word;
XTrain = word2vec(emb,wordsTrain);
YTrain_temp = dataTrain.Label;

wordsTest = dataTest.Word;
XTest = word2vec(emb, wordsTest);
YTest_temp = dataTest.Label;

% mdl = fitcsvm(XTrain,YTrain);
% [YPred,scores] = predict(mdl,XTest);
% 
% figure
% confusionchart(YTest,YPred);



YTrain = zeros(5220, 1);

for i=1:5220
    if string(YTrain_temp(i)) == "Positive"
        YTrain(i) = 1;
    end
end


net = patternnet(20);
net = configure(net, XTrain', YTrain');
% net = train(net, XTrain', YTrain');

YTest = zeros(1304, 1);

for i=1:1304
    if string(YTest_temp(i)) == "Positive"
        YTest(i) = 1;
    end
end

% YPred = net(XTest');
% plotconfusion(YPred, YTest');

textData = ["I like you", "I hate you", "I had so much fun"];
textData = textData';

documents = preprocessText(textData);
idx = ~isVocabularyWord(emb,documents.Vocabulary);
documents = removeWords(documents,idx);

words = documents.Vocabulary;
words(ismember(words,wordsTrain)) = [];

YPred = net(words);



