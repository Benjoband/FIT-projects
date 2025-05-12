-- ParseTraining.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of parsing training data from file

module ParseTraining where

import Helpers
import TrainingData

-- Parse a single line from string to [double] string
parseTrainingLine :: String -> LabeledSample
parseTrainingLine line =
  let parts = splitBy ',' line
      (featureStrs, labelPart) = splitAt (length parts - 1) parts
      features = map read featureStrs
      label = head labelPart
   in (features, label)

-- Parse file
parseTrainingFile :: FilePath -> IO [LabeledSample]
parseTrainingFile filePath = do
  content <- readFile filePath
  let ls = lines content
  return $ map parseTrainingLine ls
