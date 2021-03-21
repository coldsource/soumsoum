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

export class Crew extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("crew", this);
	}
	
	formatFloat(f, floatpart = 1) {
		return f.toFixed(floatpart).padStart(6, "\xa0");
	}
	
	render() {
		if(this.state.crew===undefined)
			return null;
		
		return (
			<div className="Crew container">
				<div className="legend">Crew</div>
				<div className="digital_display">
					<div className="row">
						Crew
						<span className="value">{this.formatFloat(this.state.crew.crew, 0)}</span>
					</div>
					<div className="row">
						O2
						<span className="value">{this.formatFloat(this.state.crew.o2_tank.dioxygen.pressure)} bar</span>
					</div>
					<div className="row">
						CO2
						<span className="value">{this.formatFloat(this.state.crew.co2_tank.carbon_dioxide.pressure)} bar</span>
					</div>
					<div className="row">
						Supplies
						<span className="value">{this.formatFloat(this.state.crew.supplies)} Kg</span>
					</div>
					<div className="row">
						Autonomy
						<span className="value">{this.formatFloat(this.state.crew.supplies_autonomy, 0)} Days</span>
					</div>
					<div className="row">
						Waste
						<span className="value">{this.formatFloat(this.state.crew.waste)} Kg</span>
					</div>
				</div>
			</div>
		);
	}
}
