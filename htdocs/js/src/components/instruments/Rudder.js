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
import {Gauge} from '../../ui/Gauge.js';

export class Rudder extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
		this.keyUp = this.keyUp.bind(this);
		
		App.registerComponent("rudder", this);
	}
	
	componentDidMount() {
		document.addEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	componentWillUnmount() {
		document.removeEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	keyDown(e) {
		if(e.key=="2")
			App.api.command({component: "rudder", action: "angle_x_minus"});
		if(e.key=="8")
			App.api.command({component: "rudder", action: "angle_x_plus"});
		if(e.key=="4")
			App.api.command({component: "rudder", action: "angle_z_plus"});
		if(e.key=="6")
			App.api.command({component: "rudder", action: "angle_z_minus"});
	}
	
	keyUp(e) {
		App.api.command({component: "rudder", action: "angle_x_neutral"});
		App.api.command({component: "rudder", action: "angle_z_neutral"});
	}
	
	render() {
		if(this.state.data===undefined)
			return null;
		
		return (
			<div className="Rudder container">
				<div className="legend">Rudder</div>
				<Gauge current={this.state.data.angle_z} min="-15" max="15" min_angle="-220" max_angle="-140" display={Math.round(this.state.data.angle_z)} />
				<Gauge current={this.state.data.angle_x} min="-15" max="15" min_angle="-130" max_angle="-50" display={Math.round(this.state.data.angle_x)} />
			</div>
		);
	}
}
