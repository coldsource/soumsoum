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

export class PitchControl extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			pump_rate: 1
		};
		
		this.pumpRateChange = this.pumpRateChange.bind(this);
		
		App.registerComponent("compensating_tank_front", this);
		App.registerComponent("compensating_tank_back", this);
	}
	
	pumpRateChange(e) {
		App.api.command({component: "compensating_tank_back", action: "pumpRateChange", rate: this.state.pump_rate});
		
		this.setState({pump_rate: e.target.value})
	}
	
	transferToFrontOn() {
		App.api.command({component: "compensating_tank_back", action: "emptyPumpOn"});
	}
	
	transferToFrontOff() {
		App.api.command({component: "compensating_tank_back", action: "emptyPumpOff"});
	}
	
	transferToBackOn() {
		App.api.command({component: "compensating_tank_back", action: "fillPumpOn"});
	}
	
	transferToBackOff() {
		App.api.command({component: "compensating_tank_back", action: "fillPumpOff"});
	}
	
	render() {
		if(this.state.compensating_tank_front===undefined || this.state.compensating_tank_back===undefined)
			return null;
		
		return (
			<div className="PitchControl container">
				<div className="legend">Pitch control</div>
				<div className="scheme">
					<div className="back_tank">{Math.round(this.state.compensating_tank_back.volume*1000)}</div>
					<div className="front_tank">{Math.round(this.state.compensating_tank_front.volume*1000)}</div>
					<SliderH name="pump_rate" value={this.state.pump_rate} onChange={this.pumpRateChange}/>
					<div className="pipe">
						<div className="front_to_back" onMouseDown={this.transferToBackOn} onMouseUp={this.transferToBackOff}><img src="images/arrow.svg" /></div>
						&#160;&#160;
						{Math.round(this.state.compensating_tank_back.flow*1000)}
						&#160;&#160;
						<div className="back_to_front" onMouseDown={this.transferToFrontOn} onMouseUp={this.transferToFrontOff}><img src="images/arrow.svg" /></div>
					</div>
				</div>
			</div>
		);
	}
}
