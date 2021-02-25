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
import {SliderH} from '../../ui/SliderH.js';

export class DepthControlTank extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			pump_rate: 1
		};
		
		this.pumpRateChange = this.pumpRateChange.bind(this);
		
		App.registerComponent("compensating_tank_center", this);
	}
	
	pumpRateChange(e) {
		App.api.command({component: "compensating_tank_center", action: "pumpRateChange", rate: this.state.pump_rate});
		
		this.setState({pump_rate: e.target.value})
	}
	
	emptyOn() {
		App.api.command({component: "compensating_tank_center", action: "emptyPumpOn"});
	}
	
	emptyOff() {
		App.api.command({component: "compensating_tank_center", action: "emptyPumpOff"});
	}
	
	fillOn() {
		App.api.command({component: "compensating_tank_center", action: "fillPumpOn"});
	}
	
	fillOff() {
		App.api.command({component: "compensating_tank_center", action: "fillPumpOff"});
	}
	
	render() {
		if(this.state.compensating_tank_center===undefined)
			return null;
		
		return (
			<div className="DepthControlTank container">
				<div className="legend">Depth control tank</div>
				<div className="scheme">
					<div className="tank">{Math.round(this.state.compensating_tank_center.volume*1000)}</div>
					<div className="fill_empty">
						<img className="fill" onMouseDown={this.fillOn} onMouseUp={this.fillOff} src="images/arrow.svg" />
						&#160;&#160;
						{Math.round(this.state.compensating_tank_center.flow*1000)}
						&#160;&#160;
						<img className="empty" onMouseDown={this.emptyOn} onMouseUp={this.emptyOff} src="images/arrow.svg" />
						<br />
					</div>
					<SliderH name="pump_rate" value={this.state.pump_rate} onChange={this.pumpRateChange}/>
				</div>
			</div>
		);
	}
}
