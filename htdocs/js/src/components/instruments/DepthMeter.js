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

export class DepthMeter extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			scale: 100,
		};
		
		App.registerComponent("moving_body", this);
		App.registerComponent("map", this);
	}
	
	scale(amount) {
		let scale = this.state.scale;
		scale += amount;
		if(scale>500)
			scale = 500;
		if(scale<50)
			scale = 50;
		
		this.setState({scale: scale});
	}
	
	render() {
		if(this.state.moving_body===undefined || this.state.map===undefined)
			return null;
		
		let image_height = 22.9;
		let image_width = 74.3;
		
		let submarine_height = image_height / this.state.scale * 100;
		
		let surface_height = (this.state.scale/2 + this.state.moving_body.position.z) / this.state.scale * 100;
		if(surface_height<0)
			surface_height = 0;
		
		let ground_height = (this.state.scale/2 - this.state.moving_body.position.z + this.state.map.depth) / this.state.scale * 100;
		if(ground_height<0)
			ground_height = 0;
		
		let water_height = 100 - surface_height - ground_height;
		
		return (
			<div className="DepthMeter container">
				<div className="legend">Depth meter</div>
				<div className="depth_meter">
					<div className="infos">
						Depth: {-this.state.map.depth}
						<br />Surface  : {this.state.moving_body.position.z<0?(-this.state.moving_body.position.z).toFixed(1):0}
						<br />Ground : {(-this.state.map.depth+this.state.moving_body.position.z).toFixed(1)}
					</div>
					<div className="zoom">
					<span className="fa fa-minus" onClick={() => this.scale(+10) }></span>
					&#160;&#160;&#160;
					<span className="fa fa-plus" onClick={() => this.scale(-10) }></span>
				</div>
					<div className="submarine" style={{height: submarine_height+'%'}}>
						<img src="images/submarine.png" style={{transform: 'rotate('+(-this.state.moving_body.attitude.x)+'rad)'}} />
						</div>
					<div className="surface" style={{height: surface_height+'%'}}></div>
					<div className="water" style={{height: water_height+'%'}}></div>
					<div className="ground" style={{height: ground_height+'%'}}></div>
				</div>
				<div className="display">
					Depth: {this.state.moving_body.position.z.toFixed(1)}
				</div>
			</div>
		);
	}
}
