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

export class ThrustSource extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("thrust", this);
	}
	
	setType(type)
	{
		App.api.command({component: "thrust", action: "setType", type: type});
	}
	
	render() {
		if(this.state.thrust===undefined)
			return null;
		
		return (
			<div className="ThrustSource container">
				<div className="legend">Source</div>
				<div>
					<span onClick={ () => this.setType("ELECTRIC") }className={this.state.thrust.type=="ELECTRIC"?"fa fa-check-circle-o":"fa fa-circle-o"}></span>
					&#160;Electric
				</div>
				<div>
					<span onClick={ () => this.setType("MECHANICAL") }className={this.state.thrust.type=="MECHANICAL"?"fa fa-check-circle-o":"fa fa-circle-o"}></span>
					&#160;Mechanical
				</div>
			</div>
		);
	}
}
