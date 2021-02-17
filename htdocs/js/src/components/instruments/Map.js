 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';

export class Map extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			track: true
		};
		
		App.registerComponent("map", this);
	}
	
	componentDidMount() {
		this.map = new OpenLayers.Map("map");
	
		this.map.addLayer(new OpenLayers.Layer.OSM('Water', [
			"https://stamen-tiles-a.a.ssl.fastly.net/watercolor/${z}/${x}/${y}.jpg",
			"https://stamen-tiles-b.a.ssl.fastly.net/watercolor/${z}/${x}/${y}.jpg",
			"https://stamen-tiles-c.a.ssl.fastly.net/watercolor/${z}/${x}/${y}.jpg",
			"https://stamen-tiles-d.a.ssl.fastly.net/watercolor/${z}/${x}/${y}.jpg"
		]));
	}
	
	render() {
		return null;
		if(this.state.map!==undefined)
		{
			let lonLatNew = new OpenLayers.LonLat(this.state.map.gps.longitude, this.state.map.gps.latitude).transform(
				new OpenLayers.Projection("EPSG:4326"),
				new OpenLayers.Projection("EPSG:900913")
			);
			
			if(this.markers===undefined)
			{
				this.map.setCenter(lonLatNew, 15);
				
				this.markers = new OpenLayers.Layer.Markers("Markers");
				this.map.addLayer(this.markers);
				
				this.marker = new OpenLayers.Marker(lonLatNew);
				this.markers.addMarker(this.marker);
			}
			
			var newPx = this.map.getLayerPxFromViewPortPx(this.map.getPixelFromLonLat(lonLatNew));
			
			if(this.state.track)
				this.map.setCenter(lonLatNew, 15);
			
			this.marker.moveTo(newPx);
		}
		
		return (
			<div className="Map">
				<input type="checkbox" checked={this.state.track} onChange={ () => this.setState({track: !this.state.track}) }/> Track
				<div id="map" className="Map"></div>
			</div>
		);
	}
}
