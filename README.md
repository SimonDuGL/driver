#The code below could be used to build a red-green map based on the dataset.
	
url = "https://raw.githubusercontent.com/SimonDuGL/driver/main/us_map.json";

gdf = gpd.read_file(url);

gdf.crs = 'epsg:4326';

gplt.polyplot(gdf, figsize=(20, 4));

gplt.choropleth(
    gdf, hue="Median_PriceToRentRatio_AllHomes", edgecolor='white', linewidth=1,
    cmap="PiYG_r", legend=True, figsize=(50, 20))

![map002](https://user-images.githubusercontent.com/101145370/165690621-7db77feb-b04a-4219-a735-79d00354bdcc.png)

#Besides, we can customize new features by using the web format converter(Matlab GUI):

#link: 

#Then, copy the result into Jupyter notebook (Python Code below):

import json

features = []; %Put the converter result into the square brackets

gdf = {
    "type": "FeatureCollection",
    "features": features
    }

with open("us_map.json", "w") as f:
    f.write(json.dumps(gdf))
