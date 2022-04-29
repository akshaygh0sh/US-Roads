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

function wasm_cpy(str){
  const ptr = Module._malloc(str.length + 1);
  const encoder = new TextEncoder();
  const encoded = encoder.encode(str);
  Module.HEAP8.subarray(ptr, ptr + str.length).set(encoded);
  Module.HEAP8[ptr + str.length] = 0;
  return ptr;
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


    Module.run();

    setTimeout(()=>{
      road_graph = Module._init(wasm_cpy(nodes), wasm_cpy(edges));
    }, 100);
}

function get_path(p1, p2){
  const shortest_path = Module._path(road_graph, p1, p2);
  const int_ptr = shortest_path/4;
  const len = Module.HEAP32[int_ptr];
  const arr = Module.HEAP32.subarray(int_ptr + 1, int_ptr + 1 + len).slice();
  Module._delete_arr(shortest_path);
  return arr;
}