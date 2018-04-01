%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function [model1 model2] = cau4(features_in)
    %khoi tao nhan training set
    in_label = ones(length(features_in), 2);
    for i = 1:2
        tmp_index = i - 1;
        in_label(:, i) = (features_in(:, 1) == tmp_index);
    end

    %khoi tao nhan test set
    out_label = ones(length(features_in), 2);
    for i = 1:2
        tmp_index = i - 1;
        out_label(:, i) = (features_in(:, 1) == tmp_index);
    end

    model1 = svmtrain(in_label(:, 1), features_in(:, 2:3), '-t 1 -c 0.01 -d 2 -q');
    model2 = svmtrain(in_label(:, 2), features_in(:, 2:3), '-t 1 -c 0.01 -d 2 -q');
end