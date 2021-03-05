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

export class ThrustElectric extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("thrust", this);
	}
	
	ratePlus() {
		App.api.command({component: "thrust", action: "ctrlPlus", type: "ELECTRIC"});
	}
	
	rateMinus() {
		App.api.command({component: "thrust", action: "ctrlMinus", type: "ELECTRIC"});
	}
	
	render() {
		if(this.state.thrust===undefined)
			return null;
		
		let bat_state = '-';
		if(this.state.thrust["ELECTRIC"].battery_rate>0)
			bat_state = 'CHARGING';
		else if(this.state.thrust["ELECTRIC"].battery_rate<0)
			bat_state = 'DISCHARGING';
		
		return (
			<div className="ThrustElectric container">
				<div className="legend">Electric</div>
				<div className="ctrl">
					<span onClick={this.rateMinus} className="fa fa-minus"></span>
					&#160;&#160;
					<span onClick={this.ratePlus} className="fa fa-plus"></span>
				</div>
				<div className="digital_display">
					<div className="row">
						Thrust
						<span className="value">{(this.state.thrust["ELECTRIC"].force/1000).toFixed(0)} kN</span>
					</div>
					<div className="row">
						Battery
						<span className="value">{bat_state}</span>
					</div>
				</div>
				<br />
				<Gauge
					current={[this.state.thrust["ELECTRIC"].rate, this.state.thrust["ELECTRIC"].ctrl]}
					min="0"
					max="1"
					display={'Power: '+Math.round(this.state.thrust["ELECTRIC"].rate*100)+'%'}
					marks={[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]}
				/>
				<Gauge
					current={this.state.thrust["ELECTRIC"].battery}
					min="0"
					max="1"
					display={'Batt: '+Math.round(this.state.thrust["ELECTRIC"].battery*100)+'%'}
					marks={[0, 0.5, 1]}
				/>
			</div>
		);
	}
}
