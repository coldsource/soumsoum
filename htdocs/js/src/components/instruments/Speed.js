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

export class Speed extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("moving_body", this);
	}
	
	formatFloat(f) {
		return f.toFixed(1).padStart(6, "\xa0");
	}
	
	render() {
		if(this.state.moving_body===undefined)
			return null;
		
		return (
			<div className="Speed container">
				<div className="legend">Speed</div>
				<div className="digital_display">
					<div className="row">
						V Speed
						<span className="value">{this.formatFloat(this.state.moving_body.speed.vertical)} m/s</span>
					</div>
					<div className="row">
						H Speed
						<span className="value">{this.formatFloat(this.state.moving_body.speed.horizontal)} m/s</span>
					</div>
				</div>
			</div>
		);
	}
}
