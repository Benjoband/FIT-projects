-- Main.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Implementation of Haskell FLP project 2025

module Main where

import Cart
import Classification
import DecisionTree
import ParseArgs
import ParseTraining
import ParseTree
import System.Environment (getArgs)

main :: IO ()
main = do
  args <- getArgs
  mode <- parseArgs args

  case mode of
    ClassificationMode treeFile dataFile -> do
      tree <- parseTreeFromFile treeFile
      classifyFromFile tree dataFile
    TrainingMode trainingFile -> do
      samples <- parseTrainingFile trainingFile
      let tree = createTreeFromSamples samples
      printTree tree 0