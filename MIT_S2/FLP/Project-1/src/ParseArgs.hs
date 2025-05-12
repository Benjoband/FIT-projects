-- ParseArgs.hs
-- Alexej Beňuš (xbenus01@stud.fit.vutbr.cz)
-- 2023-10-02
-- Parsing command-line arguments for a different tasks

module ParseArgs where

import System.Exit (exitFailure)

-- Data type to do 1st or 2nd task
data Mode
  = ClassificationMode FilePath FilePath -- Tree file, data file
  | TrainingMode FilePath -- Training file
  deriving (Show)

-- Parse command-line arguments
parseArgs :: [String] -> IO Mode
parseArgs ["-1", treeFile, dataFile] = return $ ClassificationMode treeFile dataFile
parseArgs ["-2", trainingFile] = return $ TrainingMode trainingFile
parseArgs _ = do
  putStrLn "Usage:"
  putStrLn "  flp-fun -1 <tree_file> <data_file>  # Classification mode"
  putStrLn "  flp-fun -2 <training_file>         # Training mode"
  exitFailure