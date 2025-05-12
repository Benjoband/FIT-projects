-- Classification.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of classification of data with decision tree

module Classification where

import DecisionTree
import Helpers

-- Function to classify a single data point using the decision tree
classify :: DecisionTree -> [Double] -> String
classify (Leaf label) _ = label -- Base case: If we reach a leaf, return its label
classify (Node featureIndex threshold left right) features
  | featureIndex < length features =
      if features !! featureIndex <= threshold
        then classify left features
        else classify right features
  | otherwise = error "Feature index out of bounds"

-- Read and parse a CSV file
readCSV :: FilePath -> IO [[Double]]
readCSV filePath = do
  content <- readFile filePath
  let rows = lines content
  return $ map (map read . splitBy ',') rows

-- Function to classify data from a CSV file
classifyFromFile :: DecisionTree -> FilePath -> IO ()
classifyFromFile tree filePath = do
  dataPoints <- readCSV filePath
  let results = map (classify tree) dataPoints
  mapM_ putStrLn results