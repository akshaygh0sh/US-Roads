const start_box = document.getElementById("start_node");
const end_box = document.getElementById("end_node");
const show_route = document.getElementById("show_route");

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

const styles = [
  new ol.style.Style({
    image: new ol.style.Circle({
      radius: 1,
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

const styles_highlight = [
  new ol.style.Style({
    image: new ol.style.Circle({
      radius: 5,
      fill: new ol.style.Fill({
        color: 'blue',
      }),
    }),
    geometry: function (feature) {
      // return the coordinates of the first ring of the polygon
      const coordinates = feature.getGeometry().getCoordinates()[0];
      return new ol.geom.MultiPoint(coordinates);
    },
  }),
];


function wasm_cpy(str){
  const ptr = Module._malloc(str.length + 1);
  const encoder = new TextEncoder();
  const encoded = encoder.encode(str);
  Module.HEAP8.subarray(ptr, ptr + str.length).set(encoded);
  Module.HEAP8[ptr + str.length] = 0;
  return ptr;
}

function module_loaded(){
  console.log("loaded");
  road_graph = Module._init(wasm_cpy(nodes), wasm_cpy(edges));
}

show_route.addEventListener("click", ()=>{
  const path = get_path(parseInt(start_box.value), parseInt(end_box.value));
  console.log(path);
  node_features.forEach(f=>{
    f.setStyle(styles);
  })
  path.forEach(i=>{
    node_features[i].setStyle(styles_highlight);
  })
})

window.onload = ()=>{

    
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


    node_features = new ol.format.GeoJSON().readFeatures(geojsonObject);
    const source = new ol.source.Vector({
      features: node_features,
    });
    
    const layer = new ol.layer.VectorImage({
      source: source,
      style: styles,
    });

    map = new ol.Map({
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

function get_path(p1, p2){
  const shortest_path = Module._path(road_graph, p1, p2);
  const int_ptr = shortest_path/4;
  const len = Module.HEAP32[int_ptr];
  const arr = Module.HEAP32.subarray(int_ptr + 1, int_ptr + 1 + len).slice();
  Module._delete_arr(shortest_path);
  return arr;
}