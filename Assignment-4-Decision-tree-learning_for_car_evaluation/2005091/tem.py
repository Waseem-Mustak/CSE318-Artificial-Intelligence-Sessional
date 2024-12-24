# import pandas as pd
# import matplotlib.pyplot as plt
# import os

# # Load the data
# file_path = 'data.csv'
# df = pd.read_csv(file_path, header=None)

# # Rename the columns
# column_names = [
#     "Information_gain_bestOne",
#     "Gini_impurity_bestOne",
#     "Information_gain_randomlyFromBest3",
#     "Gini_impurity_randomlyFromBest3"
# ]
# df.columns = column_names

# # Create output directory
# output_dir = "Average plot"
# os.makedirs(output_dir, exist_ok=True)

# # Generate and save a bar chart for each row of data
# for i in range(len(df)):
#     row_data = df.iloc[i]  # Extract row data
    
#     plt.figure(figsize=(8, 5))
#     plt.bar(column_names, row_data, color=['skyblue', 'orange', 'green', 'red'])
    
#     plt.title(f"Average Accuracy Comparison")
#     plt.ylabel("Average Accuracy (%)")
#     plt.xlabel("Attribute Selection Strategy")
#     plt.ylim(0, 100)
#     plt.xticks(rotation=15)
#     plt.grid(axis="y", linestyle="--", alpha=0.7)
    
#     # Annotate bars with values
#     for j, val in enumerate(row_data):
#         plt.text(j, val + 1, f"{val:.2f}", ha='center', va='bottom', fontsize=10)
    
#     # Save the plot
#     output_path = os.path.join(output_dir, f"bar_chart_row_{i+1}.png")
#     plt.tight_layout()
#     plt.savefig(output_path, dpi=300)
#     plt.close()  # Close the figure to free memory

# print(f"All 20 bar charts saved in the directory: {output_dir}")

# import pandas as pd
# import matplotlib.pyplot as plt
# import os

# # Load the data
# file_path = 'data.csv'
# df = pd.read_csv(file_path, header=None)

# # Rename the columns
# column_names = [
#     "Information_gain_bestOne",
#     "Gini_impurity_bestOne",
#     "Information_gain_randomlyFromBest3",
#     "Gini_impurity_randomlyFromBest3"
# ]
# df.columns = column_names

# # Create output directory
# output_dir = "onePlotGraphDirectory4"
# os.makedirs(output_dir, exist_ok=True)

# # X-axis: Markers for 20 data points
# x_axis = range(1, len(df) + 1)

# # Find dynamic y-axis range (adjust minimum by subtracting ~5%)
# y_min = max(min(df.min()) - 5, 80)
# y_max = min(95, max(df.max()) + 2)

# # Create a single plot
# plt.figure(figsize=(12, 7))

# # Plot each strategy as a line graph with distinct colors and markers
# # plt.plot(x_axis, df["Information_gain_bestOne"], 
# #          label="Information_gain_bestOne", marker='o', linestyle='-', color='#1f77b4')  # Blue
# # plt.plot(x_axis, df["Gini_impurity_bestOne"], 
# #          label="Gini_impurity_bestOne", marker='s', linestyle='--', color='#ff7f0e')  # Orange
# plt.plot(x_axis, df["Information_gain_randomlyFromBest3"], 
#          label="Information_gain_randomlyFromBest3", marker='^', linestyle='-.', color='#2ca02c')  # Green
# plt.plot(x_axis, df["Gini_impurity_randomlyFromBest3"], 
#          label="Gini_impurity_randomlyFromBest3", marker='d', linestyle=':', color='#d62728')  # Red

# # Title and labels
# plt.title("Accuracy Comparison Across 20 Data Points for randomly selected from best 3", fontsize=14)
# plt.xlabel("Data Point Index", fontsize=12)
# plt.ylabel("Accuracy (%)", fontsize=12)
# plt.ylim(y_min, y_max)  # Dynamic y-axis range
# plt.xticks(x_axis)  # Marks for each of the 20 data points
# plt.grid(axis="y", linestyle="--", alpha=0.7)

# # Legend
# plt.legend(loc='upper left', fontsize='small', title="Attribute Strategies", title_fontsize='medium')

# # Save the plot
# output_path = os.path.join(output_dir, "combined_accuracy_plot.png")
# plt.tight_layout()
# plt.savefig(output_path, dpi=300)
# plt.close()

# print(f"Combined accuracy graph saved in: {output_path}")


# import pandas as pd
# import matplotlib.pyplot as plt
# import os

# # Load the data
# file_path = 'data.csv'
# df = pd.read_csv(file_path, header=None)

# # Rename the columns
# column_names = [
#     "Information_gain_bestOne",
#     "Gini_impurity_bestOne",
#     "Information_gain_randomlyFromBest3",
#     "Gini_impurity_randomlyFromBest3"
# ]
# df.columns = column_names

# # Create output directory
# output_dir = "boxPlotGraphDirectory"
# os.makedirs(output_dir, exist_ok=True)

# # Create a boxplot
# plt.figure(figsize=(12, 6))


# box = plt.boxplot(
#     [df[column] for column in column_names],  
#     patch_artist=True,                       
#     labels=column_names,
#     showfliers=False  # Hide outliers
# )

# # Generate the boxplot
# # box = plt.boxplot(
# #     [df[column] for column in column_names],  # Data for boxplot
# #     patch_artist=True,                       # Enable custom fill colors
# #     labels=column_names                      # X-axis labels
# # )

# # Set custom colors for each box
# colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']  # Blue, Orange, Green, Red
# for patch, color in zip(box['boxes'], colors):
#     patch.set_facecolor(color)

# for median in box['medians']:
#     median.set(color='black', linewidth=2)


# # Title and labels
# plt.title("Accuracy Comparison (Boxplot)", fontsize=14)
# plt.ylabel("Accuracy (%)", fontsize=12)

# # Dynamic y-axis range
# y_min = max(min(df.min()) - 5, 70)  # Adjusted y-axis minimum
# y_max = min(100, max(df.max()) + 2)
# plt.ylim(y_min, y_max)

# # Grid for better readability
# plt.grid(axis='y', linestyle='--', alpha=0.7)

# # Save the plot
# output_path = os.path.join(output_dir, "accuracy_boxplot.png")
# plt.tight_layout()
# plt.savefig(output_path, dpi=300)
# plt.close()

# print(f"Boxplot saved in: {output_path}")


import matplotlib.pyplot as plt

# Modified data with updated values
modified_data = {
    'IGBest': [85.1365, 89.2791, 91.2428, 93.7717],
    'GIBest': [84.7002, 89.0023, 91.2572, 93.8006],
    'IGRandom': [78.4996, 83.5005, 86.0694, 88.9017],
    'GIRandom': [77.1077, 82.2613, 85.5202, 88.9306]
}

# X-axis labels (Training/Testing splits)
x_labels = ['20/80', '40/60', '60/40', '80/20']

# Create a single plot with 4 lines representing the 4 identifiers
plt.figure(figsize=(10, 6))

# Plot each identifier's data with specified colors
plt.plot(x_labels, modified_data['IGBest'], marker='o', label='IGBest', color='blue')
plt.plot(x_labels, modified_data['GIBest'], marker='o', label='GIBest', color='orange')
plt.plot(x_labels, modified_data['IGRandom'], marker='o', label='IGRandom', color='green')
plt.plot(x_labels, modified_data['GIRandom'], marker='o', label='GIRandom', color='red')

# Set the title and labels
plt.title('Average Accuracy for Different Data Splits (4-Digit Precision)')
plt.xlabel('Training/Testing Data Split')
plt.ylabel('Average Accuracy')

# Adjust y-axis range to make it a little bigger
plt.ylim(75, 95)

# Display legend
plt.legend()

# Add grid
plt.grid(True)

# Save the figure
plt.tight_layout()
plt.savefig('graph_accuracy_modified.png')

# Show the plot
plt.show()
