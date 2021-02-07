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
import {Slider} from '../../ui/Slider.js';

export class CompensatingTank extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
			pump_rate: 1
		};
		
		this.pumpRateChange = this.pumpRateChange.bind(this);
		this.emptyPumpOn = this.emptyPumpOn.bind(this);
		this.emptyPumpOff = this.emptyPumpOff.bind(this);
		this.fillPumpOn = this.fillPumpOn.bind(this);
		this.fillPumpOff = this.fillPumpOff.bind(this);
	}
	
	pumpRateChange(e) {
		App.api.command({component: this.props.name, action: "pumpRateChange", rate: this.state.pump_rate});
		
		this.setState({pump_rate: e.target.value})
	}
	
	emptyPumpOn(e) {
		App.api.command({component: this.props.name, action: "emptyPumpOn"});
	}
	
	emptyPumpOff(e) {
		App.api.command({component: this.props.name, action: "emptyPumpOff"});
	}
	
	fillPumpOn(e) {
		App.api.command({component: this.props.name, action: "fillPumpOn"});
	}
	
	fillPumpOff(e) {
		App.api.command({component: this.props.name, action: "fillPumpOff"});
	}
	
	render() {
		let fill = ''+Math.round(this.props.data.volume * 1000);
		let len = (''+(this.props.data.capacity*1000)).length;
		fill = fill.padStart(5, '0');
		
		return (
			<div className="CompensatingTank">
				<h2>{this.props.name}</h2>
				<Gauge current={this.props.data.volume} max={this.props.data.capacity} />
				<Slider name="pump_rate" value={this.state.pump_rate} onChange={this.pumpRateChange}/>
				<div className="fill">
					<button onMouseDown={this.emptyPumpOn} onMouseUp={this.emptyPumpOff}>-</button>
					<span className="fill">{fill}</span>
					<button onMouseDown={this.fillPumpOn} onMouseUp={this.fillPumpOff}>+</button>
				</div>
			</div>
		);
	}
}
