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

export class Acceleration extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("moving_body", this);
	}
	
	formatFloat(f) {
		return f.toFixed(2).padStart(6, "\xa0");
	}
	
	render() {
		if(this.state.moving_body===undefined)
			return null;
		
		return (
			<div className="Acceleration container">
				<div className="legend">Acceleration</div>
				<div className="digital_display">
					<div className="row">
						Vertical
						<span className="value">{this.formatFloat(this.state.moving_body.acceleration.z)} m/s</span>
					</div>
					<div className="row">
						Front
						<span className="value">{this.formatFloat(this.state.moving_body.acceleration.y)} m/s</span>
					</div>
					<div className="row">
						Side
						<span className="value">{this.formatFloat(this.state.moving_body.acceleration.x)} m/s</span>
					</div>
				</div>
			</div>
		);
	}
}
