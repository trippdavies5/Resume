from tokenize import group
import pandas as pd

# Reading the NBA games data into a DataFrame and setting the first column as the index.
df = pd.read_csv("nba_games.csv", index_col=0)

# Sorting the DataFrame by date and resetting the index.
df = df.sort_values("date")
df = df.reset_index(drop=True)

# Removing certain columns from the DataFrame.
del df["mp.1"]
del df["mp_opp.1"]
del df["index_opp"]

# Printing the DataFrame to view its contents.
print(df)

# Re-sorting the DataFrame by date and resetting the index again.
df = df.sort_values("date")
df = df.reset_index(drop=True)

# Conditionally removing columns if they exist in the DataFrame.
if 'mp.1' in df.columns:
    del df['mp.1']
if 'mp_opp.1' in df.columns:
    del df['mp_opp.1']
if 'index_opp.1' in df.columns:
    del df['index_opp']

# Function to add a target column which indicates how a team did in their next game.
def add_target(group):
    group["target"] = group["won"].shift(-1)
    return group

# Applying the function to group by team, thus adding the 'target' column.
df = df.groupby("team", group_keys=False).apply(add_target)

# Handling null values in the 'target' column by setting them to 2.
df.loc[pd.isnull(df["target"]), "target"] = 2

# Converting the 'target' column to integer type.
df["target"] = df["target"].astype(int, errors="ignore")

# Checking the value counts for the 'won' and 'target' columns.
df["won"].value_counts()
df["target"].value_counts()

# Identifying columns with null values and selecting valid columns.
nulls = pd.isnull(df).sum()
nulls = nulls[nulls > 0]
valid_columns = df.columns[~df.columns.isin(nulls.index)]

# Creating a new DataFrame with only valid columns.
df = df[valid_columns].copy()

# Importing necessary modules from scikit-learn for machine learning.
from sklearn.linear_model import RidgeClassifier
from sklearn.feature_selection import SequentialFeatureSelector
from sklearn.model_selection import TimeSeriesSplit

# Initializing a Ridge Classifier.
rr = RidgeClassifier(alpha=1)

# Setting up a Time Series Split for cross-validation.
split = TimeSeriesSplit(n_splits=3)

# Initializing Sequential Feature Selector with Ridge Classifier.
sfs = SequentialFeatureSelector(rr, n_features_to_select=30, direction="forward", cv=split, n_jobs=1)

# Specifying columns to be removed before feature selection.
removed_columns = ["season", "date", "won", "target", "team", "team_opp"]
selected_columns = df.columns[~df.columns.isin(removed_columns)]

# Initializing a Min-Max Scaler.
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()

# Scaling the selected columns in the DataFrame.
df[selected_columns] = scaler.fit_transform(df[selected_columns])

# Fitting the Sequential Feature Selector on the DataFrame.
sfs.fit(df[selected_columns], df["target"])

# Retrieving the selected predictors.
predictors = list(selected_columns[sfs.get_support()])

# Backtesting predictions using the selected predictors and Ridge Classifier.
predictions = backtest(df, rr, predictors)

# Importing accuracy_score to evaluate the model.
from sklearn.metrics import accuracy_score

# Computing the accuracy of the predictions.
accuracy_score(predictions["actual"], predictions["prediction"])

# Analyzing the win rate for home games.
df.groupby(["home"]).apply(lambda x: x[x["won"] == 1].shape[0] / x.shape[0])

# Creating a new DataFrame with rolling averages.
df_rolling = df[list(selected_columns) + ["won", "team", "season"]]

# Function to compute team averages using a rolling window.
def find_team_averages(team):
    rolling = team.rolling(10).mean()
    return rolling

# Applying the function to compute rolling averages for each team and season.
df_rolling = df_rolling.groupby(["team", "season"], group_keys=False).apply(find_team_averages)

# Renaming columns to indicate rolling averages.
rolling_cols = [f"{col}_10" for col in df_rolling.columns]
df_rolling.columns = rolling_cols

# Concatenating the rolling averages with the original DataFrame.
df = pd.concat([df, df_rolling], axis=1)

# Dropping rows with null values.
df = df.dropna()

# Function to shift a column for each team.
def shift_col(team, col_name):
    next_col = team[col_name].shift(-1)
    return next_col

# Function to apply the shift to a specific column.
def add_col(df, col_name):
    return df.groupby("team", group_keys=False).apply(lambda x: shift_col(x, col_name))

# Adding columns for the next game's attributes.
df["home_next"] = add_col(df, "home")
df["team_opp_next"] = add_col(df, "team_opp")
df["date_next"] = add_col(df, "date")

# Merging the DataFrame with itself to align team data with their next opponent.
full = df.merge(df[rolling_cols + ["team_opp_next", "date_next", "team"]], 
                left_on=["team", "date_next"], right_on=["team_opp_next","date_next"])

# Viewing the merged DataFrame structure.
full[["team_x", "team_opp_next_x", "team_y", "team_opp_next_y", "date_next"]]

# Removing columns that are of object type and other specified columns.
removed_columns = list(full.columns[full.dtypes == "object"]) + removed_columns
selected_columns = full.columns[~full.columns.isin(removed_columns)]

# Fitting the Sequential Feature Selector on the merged DataFrame.
sfs.fit(full[selected_columns], full["target"])

# Selecting predictors from the merged DataFrame.
predictors = list(selected_columns[sfs.get_support()])

# Calculating the accuracy score of the predictions.
accuracy_score(predictions["actual"], predictions["prediction"])

# This code processes NBA game data, trains a machine learning model 
# using Ridge Classifier, and makes predictions about game outcomes. 
# It includes data cleaning, feature selection, scaling, and model evaluation. 
# The model is trained to predict the outcome of a team's next game based on historical data.