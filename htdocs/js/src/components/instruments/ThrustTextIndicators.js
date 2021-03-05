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
import {TextDisplay} from '../../ui/TextDisplay.js';

export class ThrustTextIndicators extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {};
		
		App.registerComponent("thrust", this);
	}
	
	render() {
		if(this.state.thrust===undefined)
			return null;
		
		let thrust = this.state.thrust;
		
		return (
			<div className="TextIndicators container">
				<TextDisplay text="ELECTRIC ON" type={thrust.ELECTRIC.targeted_rate>0 && thrust.type!='ELECTRIC'?"warning":"notice"} status={thrust.ELECTRIC.targeted_rate>0?"on":"off"} />
				<br /><TextDisplay text="ELECTRIC SRC" type="warning" status={thrust.ELECTRIC.ctrl>0 && thrust.ELECTRIC.targeted_rate==0?"on":"off"} />
				<br /><TextDisplay text="BATT CHARGING" type="notice" status={thrust.ELECTRIC.battery!=1 && thrust.ELECTRIC.battery_rate>0?"on":"off"} />
				<br /><TextDisplay text="BATT LOW" type="warning" status={thrust.ELECTRIC.battery<0.1?"on":"off"} />
				<br /><TextDisplay text="MECHANICAL ON" type={thrust.MECHANICAL.targeted_rate>0 && thrust.type!='MECHANICAL'?"warning":"notice"} status={thrust.MECHANICAL.targeted_rate>0?"on":"off"} />
				<br /><TextDisplay text="MECHANICAL SRC" type="warning" status={thrust.MECHANICAL.ctrl>0 && thrust.MECHANICAL.targeted_rate==0?"on":"off"} />
			</div>
		);
	}
}
