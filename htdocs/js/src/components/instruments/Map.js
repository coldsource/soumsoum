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
		this.map = new ol.Map({
			target: 'map',
			layers: [
				new ol.layer.Tile({
					source: new ol.source.OSM({
						//url: "https://stamen-tiles-{a-d}.a.ssl.fastly.net/watercolor/{z}/{x}/{y}.jpg"
						maxZoom: 18
					})
				})
			],
			view: new ol.View({
				zoom: 15
			})
		});
	}
	
	render() {
		if(this.state.map!==undefined)
		{
			this.map.updateSize();
			
			let lonlat = ol.proj.transform([this.state.map.gps.longitude, this.state.map.gps.latitude], 'EPSG:4326', 'EPSG:3857');
			
			if(this.marker===undefined)
			{
				this.marker = new ol.geom.Point(lonlat);
				
				let layer = new ol.layer.Vector({
					source: new ol.source.Vector({
						features: [
							new ol.Feature({
								geometry: this.marker
							})
						]
					})
				});
				this.map.addLayer(layer);
			}
			
			if(this.state.track)
				this.map.getView().setCenter(lonlat);
			
			this.marker.setCoordinates(lonlat);
		}
		
		return (
			<div className="Map">
				<input type="checkbox" checked={this.state.track} onChange={ () => this.setState({track: !this.state.track}) }/> Track
				<div id="map" className="Map"></div>
			</div>
		);
	}
}
