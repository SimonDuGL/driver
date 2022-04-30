#The code below could be used to build a red-green map based on the dataset.
	
url = "https://raw.githubusercontent.com/SimonDuGL/driver/main/us_map.json";

gdf = gpd.read_file(url);

gdf.crs = 'epsg:4326';

gplt.polyplot(gdf, figsize=(20, 4));

gplt.choropleth(
    gdf, hue="Median_PriceToRentRatio_AllHomes", edgecolor='white', linewidth=1,
    cmap="PiYG_r", legend=True, figsize=(50, 20))

![map002](https://user-images.githubusercontent.com/101145370/165690621-7db77feb-b04a-4219-a735-79d00354bdcc.png)

#Besides, we can customize new features by using a Matlab GUI:

Online platform Link: https://matlab.mathworks.com/

GUI file link: https://github.com/SimonDuGL/driver/commit/8eeb9e24edb4ebec543bb833c926dec39c19ed49/formatConverter.mlapp
![20220430181916Administrator](https://user-images.githubusercontent.com/101145370/166125737-b6bc1461-597a-45f0-9be4-c519b79896be.png)

#Then, copy the Result into the Jupyter notebook (Python Code below):

import json

features = []; %Put the converter Result into the square brackets

gdf = {
    "type": "FeatureCollection",
    "features": features
    }

with open("us_map.json", "w") as f:
    f.write(json.dumps(gdf))
