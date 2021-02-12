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
import {GaugeHalf} from '../../ui/GaugeHalf.js';

export class DivingPlane extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
	}
	
	componentDidMount() {
		document.addEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	componentWillUnmount() {
		document.removeEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	keyDown(e) {
		if(e.key=="+")
			App.api.command({component: this.props.name, action: "rate_plus"});
		if(e.key=="-")
			App.api.command({component: this.props.name, action: "rate_minus"});
		if(e.key=="9")
			App.api.command({component: this.props.name, action: "surface"});
		/*if(e.key=="6")
			App.api.command({component: this.props.name, action: "neutral"});*/
		if(e.key=="3")
			App.api.command({component: this.props.name, action: "dive"});
	}
	
	render() {
		let fill = ''+Math.round(this.props.data.volume * 1000);
		let len = (''+(this.props.data.capacity*1000)).length;
		fill = fill.padStart(5, '0');
		
		return (
			<div className="DivingPlane">
				<h2>{this.props.name}</h2>
				<GaugeHalf current={[this.props.data.targeted_tilt, this.props.data.tilt]} min="-3" max="3" />
			</div>
		);
	}
}
