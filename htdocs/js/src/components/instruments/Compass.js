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

export class Compass extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("moving_body", this);
	}
	
	render() {
		if(this.state.moving_body===undefined)
			return null;
		
		return (
			<div className="Compass container">
				<div className="legend">Compass</div>
				<div className="compass">
					<div style={{transform: 'rotate(-'+this.state.moving_body.compass+'deg)'}}>
						<div style={{transform: 'rotate(+'+this.state.moving_body.compass+'deg)'}}></div>
					</div>
				</div>
				<div className="display">{this.state.moving_body.compass.toFixed(1)}</div>
			</div>
		);
	}
}
