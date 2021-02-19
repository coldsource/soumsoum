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

export class Thrust extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
		this.keyUp = this.keyUp.bind(this);
		
		App.registerComponent("thrust", this);
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
		if(e.key=="+")
			App.api.command({component: "thrust", action: "rate_plus"});
		if(e.key=="-")
			App.api.command({component: "thrust", action: "rate_minus"});
	}
	
	keyUp(e) {
		App.api.command({component: "thrust", action: "angle_x_neutral"});
		App.api.command({component: "thrust", action: "angle_z_neutral"});
	}
	
	render() {
		if(this.state.thrust===undefined)
			return null;
		
		return (
			<div className="Thrust container">
				<div className="legend">Thrust</div>
				<Gauge
					current={[this.state.thrust.targeted_rate, this.state.thrust.rate]}
					min="0"
					max="1"
					display={'Power: '+Math.round(this.state.thrust.rate*100)+'%'}
					marks={[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]}
				/>
			</div>
		);
	}
}
