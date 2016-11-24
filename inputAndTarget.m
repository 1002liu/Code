function [ inputs,targets ] = inputAndTarget( M )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
[a,b]=size(M);
inputs = M(:,1:b-1);
targets = M(:,b);

end

