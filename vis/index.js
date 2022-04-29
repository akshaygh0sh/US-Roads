function make_feature(point){
    const [id, x, y] = point.split(' ');
    return {
        'type': 'Feature',
        'geometry': {
          'type': 'Polygon',
          'coordinates': [
              [
                [parseFloat(x) * 730 - 14435000, parseFloat(y) * 550 + 1725000],
              ],
            ],
        },
    }
}

window.onload = ()=>{

    const styles = [
        /* We are using two different styles for the polygons:
         *  - The first style is for the polygons themselves.
         *  - The second style is to draw the vertices of the polygons.
         *    In a custom `geometry` function the vertices of a polygon are
         *    returned as `MultiPoint` geometry, which will be used to render
         *    the style.
         */
        // new ol.style.Style({
        //   stroke: new ol.style.Stroke({
        //     color: 'blue',
        //     width: 3,
        //   }),
        //   fill: new ol.style.Fill({
        //     color: 'rgba(0, 0, 255, 0.1)',
        //   }),
        // }),
        new ol.style.Style({
          image: new ol.style.Circle({
            radius: 5,
            fill: new ol.style.Fill({
              color: 'orange',
            }),
          }),
          geometry: function (feature) {
            // return the coordinates of the first ring of the polygon
            const coordinates = feature.getGeometry().getCoordinates()[0];
            return new ol.geom.MultiPoint(coordinates);
          },
        }),
      ];

    const geojsonObject = {
        'type': 'FeatureCollection',
        'crs': {
          'type': 'name',
          'properties': {
            'name': 'EPSG:3857',
          },
        },
        'features': nodes.split('\n').map(make_feature),
        // 'features': [
        //   {
        //     'type': 'Feature',
        //     'geometry': {
        //       'type': 'Polygon',
        //       'coordinates': [
        //           [
        //           [-5e6, 6e6],
        //           [-5e6, 8e6],
        //           [-3e6, 8e6],
        //           [-3e6, 6e6],
        //           [-5e6, 6e6],
        //           ],
        //         ],
        //     },
        //   },
        //   {
        //     'type': 'Feature',
        //     'geometry': {
        //       'type': 'Polygon',
        //       'coordinates': [
        //         [
        //           [-2e6, 6e6],
        //           [-2e6, 8e6],
        //           [0, 8e6],
        //           [0, 6e6],
        //           [-2e6, 6e6],
        //         ],
        //       ],
        //     },
        //   },
        //   {
        //     'type': 'Feature',
        //     'geometry': {
        //       'type': 'Polygon',
        //       'coordinates': [
        //         [
        //           [1e6, 6e6],
        //           [1e6, 8e6],
        //           [3e6, 8e6],
        //           [3e6, 6e6],
        //           [1e6, 6e6],
        //         ],
        //       ],
        //     },
        //   },
        //   {
        //     'type': 'Feature',
        //     'geometry': {
        //       'type': 'Polygon',
        //       'coordinates': [
        //         [
        //           [-2e6, -1e6],
        //           [-1e6, 1e6],
        //           [0, -1e6],
        //           [-2e6, -1e6],
        //         ],
        //       ],
        //     },
        //   },
        // ],
      };

    const source = new ol.source.Vector({
    features: new ol.format.GeoJSON().readFeatures(geojsonObject),
    });
    
    const layer = new ol.layer.VectorImage({
    source: source,
    style: styles,
    });

    var map = new ol.Map({
        target: 'map',
        layers: [
            new ol.layer.Tile({
            source: new ol.source.OSM()
            }),
            layer
        ],
        view: new ol.View({
            center: ol.proj.fromLonLat([-75, 40]),
            zoom: 4
        })
    });

}